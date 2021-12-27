#include <stdio.h>
#include <string.h>
#include <esp_log.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mdns.h"
#include "ipp.h"
#include "ipp_server.h"
#include "esp_http_server.h"
#include "../internalhub/internal_sysinfo.h"
#include "../internalhub/internalhub.h"
#include "../internalhub/internal_printinfo.h"
#include "common.h"
#include "../printclient/pc_dn_msg.h"
#include "../printclient/printclient.h"
#include "pp_module_mmu.h"
#include "esp_heap_caps.h"


//#undef ESP_LOGI
//#define ESP_LOGI( tag, format, ... )

#define TAG "ippserver"

#define IPP_SERVER_BUF_SIZE_MAX   (3072)

#if 1
#undef ESP_LOGI
#undef ESP_LOGW
#undef ESP_LOGE
#define ESP_LOGI(x, ...)
#define ESP_LOGW(x, ...)
#define ESP_LOGE(x, ...)
#endif


static ipp_attribute *printer_attr = NULL;
static ipp_attribute *job_attr = NULL;


static ipp_server_info_t *ipp_server_info = NULL;
static char *ipp_server_rsp_buf = NULL;
static httpd_handle_t http_server = NULL;
static bool ippserver_network_connect_sta = false;
static bool is_need_ippserver_reinit_flg = false, is_need_ippserver_deinit_flg = false;
static xSemaphoreHandle ippserver_semap_handle = NULL;
static int g_job_id = 0;

ipp_server_info_t* ipp_get_server_info(void)
{
	return ipp_server_info;
}

int ipp_get_job_id(void)
{
	return g_job_id;
}


static esp_err_t ipp_post_handler(httpd_req_t *req)
{
    char*  buffer = ipp_server_rsp_buf;
    size_t buf_len;
    int version, op_status, request_id;

	printf( "ipp MALLOC_CAP_SPIRAM total=%d free=%d\n", heap_caps_get_total_size(MALLOC_CAP_SPIRAM), heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
	printf( "ipp MALLOC_CAP_INTERNAL total=%d free=%d\n", heap_caps_get_total_size(MALLOC_CAP_INTERNAL), heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
	

    ESP_LOGI(TAG, "=======================================");
    buf_len = httpd_req_get_hdr_value_len(req, "Content-Type") + 1;

    if (buf_len > 1)
    {
		memset(buffer, 0, buf_len);
        if (httpd_req_get_hdr_value_str(req, "Content-Type",
                                buffer, buf_len) == ESP_OK)
        {
            ESP_LOGI(TAG, "Content-Type: %s", buffer);
        }
    }

    if (req->content_len == 0)
    {
        version = (req->chunk_ippstate[0] << 8) | req->chunk_ippstate[1];
        op_status   = (req->chunk_ippstate[2] << 8) | req->chunk_ippstate[3];
        request_id  = (((((req->chunk_ippstate[4] << 8) | req->chunk_ippstate[5]) << 8) |
                          req->chunk_ippstate[6]) << 8) | req->chunk_ippstate[7];
        ESP_LOGI(TAG, "version=%d.%d, op_status=%04x, request_id=%d",
                        req->chunk_ippstate[0], req->chunk_ippstate[1], 
                        op_status, request_id);
        goto __ipp_operate;
    }

    ipp_tag_t      tag;      /* Current tag */
    int            n;        /* Length of data */
    int remaining = req->content_len;

    memset(buffer, 0, remaining);
    if (buffer == NULL)
    {
        return ESP_OK;
    }

    buf_len = 0;
    if (remaining >= 8)
    {
        while (HTTPD_SOCK_ERR_TIMEOUT == httpd_req_recv(req, buffer, 8)) {;}
        remaining -= 8;
    }

    /*
    * Get the request header...
    */
    version = (buffer[0] << 8) | buffer[1];
    op_status   = (buffer[2] << 8) | buffer[3];
    request_id  = (((((buffer[4] << 8) | buffer[5]) << 8) |
                              buffer[6]) << 8) | buffer[7];

    ESP_LOGI(TAG, "version=%d.%d, op_status=%04x, request_id=%d",
                    buffer[0], buffer[1], op_status, request_id);

    while (remaining > 0)
    {
      if (remaining >= 1)
      {
          memset(buffer, 0, remaining);
          while (HTTPD_SOCK_ERR_TIMEOUT == httpd_req_recv(req, buffer, 1)) {;}
          remaining -= 1;
      }

      tag = (ipp_tag_t)buffer[0];
      if (tag == IPP_TAG_EXTENSION)
      {
          /*
          * Read 32-bit "extension" tag...
          */

          if (remaining >= 4)
          {
              memset(buffer, 0, remaining);
              while (HTTPD_SOCK_ERR_TIMEOUT == httpd_req_recv(req, buffer, 4)) {;}
              remaining -= 4;
          }

          tag = (ipp_tag_t)((((((buffer[0] << 8) | buffer[1]) << 8) |
                                        buffer[2]) << 8) | buffer[3]);
          if (tag & IPP_TAG_CUPS_CONST)
          {
              /*
              * Fail if the high bit is set in the tag...
              */
              ESP_LOGI(TAG,"Fail if the high bit is set in the tag 0x%02x.", tag);
              return (IPP_STATE_ERROR);
          }
      }

      if (tag == IPP_TAG_END)
      {
          /*
          * No more attributes left...
          */
          ESP_LOGW(TAG,"IPP_TAG_END");
          break;
      }
      else if (tag == IPP_TAG_ZERO) // || tag == IPP_TAG_OPERATION)
      {
          ESP_LOGI(TAG,"bad tag 0x%02x.", tag);
          return (IPP_STATE_ERROR);
      }
      else if (tag < IPP_TAG_UNSUPPORTED_VALUE)
      {
          /*
          * Group tag...  Set the current group and continue...
          */
          ESP_LOGW(TAG,"Group 0x%02x", tag);
          continue;
      }

      ESP_LOGI(TAG,"----- Key Tag 0x%02x -----", tag);
      /*
      * Get the name...
      */
      if (remaining >= 2)
      {
          memset(buffer, 0, remaining);
          while (HTTPD_SOCK_ERR_TIMEOUT == httpd_req_recv(req, buffer, 2)) {;}
          remaining -= 2;
      }

      n = (buffer[0] << 8) | buffer[1];
      ESP_LOGI(TAG,"Key name length=%d", n);

      if (n == 0 && tag != IPP_TAG_MEMBERNAME && tag != IPP_TAG_END_COLLECTION)
      {
          ESP_LOGI(TAG, "------------------------");
      }
      else if (tag == IPP_TAG_MEMBERNAME)
      {
          if (n)
          {
              ESP_LOGI(TAG, "member name not empty.");
          }
      }
      else if (tag != IPP_TAG_END_COLLECTION)
      {
          /*
          * New attribute; read the name and add it...
          */
          if (remaining >= n)
          {
              memset(buffer, 0, remaining);
              while (HTTPD_SOCK_ERR_TIMEOUT == httpd_req_recv(req, buffer, n)) {;}
              remaining -= n;
          }

          buffer[n] = '\0';
          ESP_LOGI(TAG,"Key name=\"%s\"", buffer);
      }

      if (remaining >= 2)
      {
          memset(buffer, 0, remaining);
          while (HTTPD_SOCK_ERR_TIMEOUT == httpd_req_recv(req, buffer, 2)) {;}
          remaining -= 2;
      }
      n = (buffer[0] << 8) | buffer[1];
      ESP_LOGI(TAG, "Key value length=%d", n);

      switch (tag)
      {
          case IPP_TAG_INTEGER :
          case IPP_TAG_ENUM :
          if (n != 4)
          {
              break;
          }

          if (remaining >= 4)
          {
              memset(buffer, 0, remaining);
              while (HTTPD_SOCK_ERR_TIMEOUT == httpd_req_recv(req, buffer, 4)) {;}
              remaining -= 4;
          }
          n = (((((buffer[0] << 8) | buffer[1]) << 8) | buffer[2]) << 8) |
          buffer[3];
          ESP_LOGI(TAG, "Key value=\"%d\"", n);
          break;

          case IPP_TAG_BOOLEAN :
          if (n != 1)
          {
              break;
          }
          if (remaining >= 1)
          {
              memset(buffer, 0, remaining);
              while (HTTPD_SOCK_ERR_TIMEOUT == httpd_req_recv(req, buffer, 1)) {;}
              remaining -= 1;
          }
          ESP_LOGI(TAG, "Key value=\"%d\"", n);
          break;

          case IPP_TAG_UNSUPPORTED_VALUE :
          case IPP_TAG_DEFAULT :
          case IPP_TAG_UNKNOWN :
          case IPP_TAG_NOVALUE :
          case IPP_TAG_NOTSETTABLE :
          case IPP_TAG_DELETEATTR :
          case IPP_TAG_ADMINDEFINE :
          break;

          case IPP_TAG_TEXT :
          case IPP_TAG_NAME :
          case IPP_TAG_RESERVED_STRING :
          case IPP_TAG_KEYWORD :
          case IPP_TAG_URI :
          case IPP_TAG_URISCHEME :
          case IPP_TAG_CHARSET :
          case IPP_TAG_LANGUAGE :
          case IPP_TAG_MIMETYPE :
          if (remaining >= n)
          {
              memset(buffer, 0, remaining);
              while (HTTPD_SOCK_ERR_TIMEOUT == httpd_req_recv(req, buffer, n)) {;}
              remaining -= n;
          }
          ESP_LOGI(TAG, "Key value=\"%s\"", buffer);
          break;

          default:
            ESP_LOGI(TAG, "Key unkown tag=%d", tag);
            break;
      }
    }

__ipp_operate:

    buf_len = 0;
	memset(buffer, 0, IPP_SERVER_BUF_SIZE_MAX);
    if (buffer == NULL) {
        ESP_LOGI(TAG, "=============== malloc ERROR =================");
        return ESP_OK;
    }

    switch(op_status)
    {
        case IPP_OP_GET_PRINTER_ATTRIBUTES:
		{
			internal_printerinfo *print_info = internal_printerinfo_instance();		
	        ESP_LOGI(TAG, "IPP_OP_GET_PRINTER_ATTRIBUTES: %d", print_info->enum_state);
			printf("IPP_OP_GET_PRINTER_ATTRIBUTES\n");
			
			if (print_info->enum_state == PRINTER_STATE_IDLE)
			{
				ipp_get_printer_attributes(&printer_attr, IPP_PSTATE_IDLE);
			}
			else if (print_info->enum_state == PRINTER_STATE_PROCESSING)
			{
				ipp_get_printer_attributes(&printer_attr, IPP_PSTATE_PROCESSING);
			}
			else
			{
				ipp_get_printer_attributes(&printer_attr, IPP_PSTATE_STOPPED);
			}

	        op_status = 0x01;
	        buf_len = ippAttrToRespBuff(printer_attr, version, op_status, request_id, buffer, IPP_SERVER_BUF_SIZE_MAX);
	        break;
        }

        case IPP_OP_VALIDATE_JOB:
	        ESP_LOGI(TAG, "IPP_OP_VALIDATE_JOB");
			
			printf("IPP_OP_VALIDATE_JOB\n");
			
	        op_status = 0x01;
	        buf_len = ippAttrToRespBuff(NULL, version, op_status, request_id, buffer, IPP_SERVER_BUF_SIZE_MAX);
	        break;

        case IPP_OP_CREATE_JOB:
	        ESP_LOGI(TAG, "IPP_OP_CREATE_JOB");
			im_set_skip_reconnect_flg(true);
			printf("IPP_OP_CREATE_JOB\n");

			
			g_job_id++;
	        ipp_get_job_attributes(&job_attr, IPP_JSTATE_HELD);
	        op_status = 0x01;
	        buf_len = ippAttrToRespBuff(job_attr, version, op_status, request_id, buffer, IPP_SERVER_BUF_SIZE_MAX);
	        break;

        case IPP_OP_SEND_DOCUMENT:
	        ESP_LOGI(TAG, "IPP_OP_SEND_DOCUMENT");
	        op_status = 0x01;
			printf("IPP_OP_SEND_DOCUMENT\n");


			PcDnMsgIppServerNotifyPrinting();
	        ipp_get_job_attributes(&job_attr, IPP_JSTATE_HELD);
	        buf_len = ippAttrToRespBuff(job_attr, version, op_status, request_id, buffer, IPP_SERVER_BUF_SIZE_MAX);
	        break;

        case IPP_OP_CANCEL_JOB:
	        ESP_LOGI(TAG, "IPP_OP_CANCEL_JOB");
			im_set_skip_reconnect_flg(false);

			
			printf("IPP_OP_CANCEL_JOB\n");
		
	        ipp_get_job_attributes(&job_attr, IPP_JSTATE_CANCELED);
	        op_status = 0x01;
	        buf_len = ippAttrToRespBuff(job_attr, version, op_status, request_id, buffer, IPP_SERVER_BUF_SIZE_MAX);
	        break;

        case IPP_OP_GET_JOB_ATTRIBUTES:
	        ESP_LOGI(TAG, "IPP_OP_GET_JOB_ATTRIBUTES");
	        op_status = 0x01;

			printf("IPP_OP_GET_JOB_ATTRIBUTES\n");

			internal_jobinfo *job_info = internal_jobinfo_instance();

			if ((ipp_jstate_t)job_info->jobsta != IPP_JSTATE_PROCESSING) {
				im_set_skip_reconnect_flg(false);
			}
	        ipp_get_job_attributes(&job_attr, (ipp_jstate_t)job_info->jobsta);

	        buf_len = ippAttrToRespBuff(job_attr, version, op_status, request_id, buffer, IPP_SERVER_BUF_SIZE_MAX);
	        break;

        default:
        break;
    }

#if 0
    ESP_LOGI(TAG, "buf_len = %d\n", buf_len);

    /* S.DEBUG.. */
    char buff_ascii[33] = {0};
    int j=0;
    for (int i=0; i<buf_len; i++) {
        if (buffer[i] == 0x00) {
            buff_ascii[j] = ' '; 
        } else if (buffer[i] < 0x20 || buffer[i] > 0x7F) {
            buff_ascii[j] = '.';
        } else {
            buff_ascii[j] = buffer[i];
        }

        j++;
        if (j >= 31) {
            buff_ascii[j+1] = '\0';
            printf("%s", buff_ascii);
            j = 0;
        }
    }

    if (j > 0) {
        buff_ascii[j] = '\0';
        printf("%s\n", buff_ascii);
    }
    /* E.DEBUG.. */
#endif

    httpd_resp_set_hdr(req, "Connection", "close");
    httpd_resp_set_hdr(req, "X-Frame-Options", "SAMEORIGIN");
    httpd_resp_set_hdr(req, "X-XSS-Protection", "1; mode=block");
    httpd_resp_set_hdr(req, "Strict-Transport-Security", "max-age=31536000;");
    httpd_resp_set_hdr(req, "Cache-Control", "max-age=0, no-store, no-cache");

    httpd_resp_set_status(req, HTTPD_200);
	
    if (ESP_OK == httpd_resp_send(req, buffer, buf_len)) {
    ESP_LOGI(TAG, "=============== Respond OK =================");
    }

    ippReleaseAttr(&job_attr);
    ippReleaseAttr(&printer_attr);

    return ESP_OK;
}

static esp_err_t ipp_job_post_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "=============== ipp_job_post_handler OK =================");
    return ESP_OK;
}

static const httpd_uri_t ipp_print = {
    .uri       = "/ipp/print",
    .method    = HTTP_POST,
    .handler   = ipp_post_handler,
    .user_ctx  = NULL,
    .printdata_write = PcDnMsgPrintCacheWriteIo,
};

static const httpd_uri_t ipp_print_job = {
    .uri       = "/ipp/print/Job-1",
    .method    = HTTP_POST,
    .handler   = ipp_job_post_handler,
    .user_ctx  = NULL
};

static void ippserver_mdns_init(int ipp_port)
{
    //initialize mDNS
    ESP_ERROR_CHECK( mdns_init() );
    //set mDNS hostname (required if you want to advertise services)
    ESP_ERROR_CHECK( mdns_hostname_set(ipp_server_info->host_name) );
    ESP_LOGI(TAG, "mdns hostname set to: [%s]", ipp_server_info->host_name);
    //set default mDNS instance name
    ESP_ERROR_CHECK( mdns_instance_name_set("IPP Server") );

    //structure with TXT records
    mdns_txt_item_t serviceTxtData[CONFIG_MDNS_MAX_SERVICES] = {
        {"txtvers","1"},
        {"qtotal","1"},
        {"adminurl", ipp_server_info->url},
        {"rp", "ipp/print"},
        {"ty", "ipp/print"},
        {"note", ""},
        {"product", "(PP "PROJECT_NAME" Series)"},
        {"printer-state", "3"},
        {"printer-type", "0x3006"},
        {"Binary", "T"}
    };

    //initialize service
    ESP_ERROR_CHECK( mdns_service_add(ipp_server_info->instance_name, "_ipp", "_tcp", ipp_port, serviceTxtData, CONFIG_MDNS_MAX_SERVICES) );
	ESP_ERROR_CHECK( mdns_service_txt_item_set("_ipp", "_tcp", "DevType", "0x04") );
	ESP_ERROR_CHECK( mdns_service_txt_item_set("_ipp", "_tcp", "Transparent", "T") );
    ESP_ERROR_CHECK( mdns_service_txt_item_set("_ipp", "_tcp", "mac", ipp_server_info->mac) );
    ESP_ERROR_CHECK( mdns_service_txt_item_set("_ipp", "_tcp", "URF", "DM3") );
    ESP_ERROR_CHECK( mdns_service_txt_item_set("_ipp", "_tcp", "pdl",
                                               "application/octet-stream,"
                                               "application/PCLm,"
                                               "image/pwg-raster") );
}

#if 0
esp_err_t paperang_mdns_init(void)
{
    //initialize mDNS
    char *hostname = "esp32s2-mdns";

    ESP_ERROR_CHECK( mdns_init() );
    //set mDNS hostname (required if you want to advertise services)
    ESP_ERROR_CHECK( mdns_hostname_set(hostname) );
    ESP_LOGI(TAG, "mdns hostname set to: [%s]", hostname);
    //set default mDNS instance name
    ESP_ERROR_CHECK( mdns_instance_name_set("IPP Server") );

    //structure with TXT records
    mdns_txt_item_t PaperangTxtData[5] = {
        {"LinkState", "Online"},
        {"SN", "X200P001HW0016"},
        {"LAN-Mac", "112233445577"},
        {"DevType", "0x02"},
        {"Product", "Paperang_A4"}
    };

    //initialize service
    ESP_ERROR_CHECK( mdns_service_add("paperang_a4", "_paperang", "_udp", 0, PaperangTxtData, 5) );

    return ESP_OK;
}
#endif

static void ippserver_start(void)
{
	httpd_config_t config = HTTPD_DEFAULT_CONFIG();
	// Start the httpd server
	config.server_port = 631;
	
	snprintf(ipp_server_info->url, 48, "http://%s.local:%d/ipp/print", ipp_server_info->host_name, config.server_port);
	
	ippserver_mdns_init(config.server_port);
	
	ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
	
	if (httpd_start(&http_server, &config) == ESP_OK) {
		// Set URI handlers
		ESP_LOGI(TAG, "Registering URI handlers");
		httpd_register_uri_handler(http_server, &ipp_print);
		httpd_register_uri_handler(http_server, &ipp_print_job);
	}
}

void ippserver_stop(void)
{
    // Stop the httpd server
    if (http_server == NULL) {
		ESP_LOGI(TAG, "ippserver_stop no need");
	}
	
    httpd_stop(http_server);
	http_server = NULL;

	mdns_free();
}

static void network_connect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
	ippserver_network_connect_sta = true;
	is_need_ippserver_reinit_flg = true;
	is_need_ippserver_deinit_flg = false;
	xSemaphoreGive(ippserver_semap_handle);
}

static void network_disconnect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
	ippserver_network_connect_sta = false;
	is_need_ippserver_reinit_flg = false;
	is_need_ippserver_deinit_flg =  true;
	xSemaphoreGive(ippserver_semap_handle);
}

void ippserver_task(void *param)
{
	while (true) {

		if (!is_need_ippserver_reinit_flg || !is_need_ippserver_deinit_flg) {
			xSemaphoreTake(ippserver_semap_handle, portMAX_DELAY);
		}
		
		ESP_LOGW(TAG, "RECV semap ippserver_task: %d %d %d...", ippserver_network_connect_sta, 
							is_need_ippserver_reinit_flg, is_need_ippserver_deinit_flg);
		if (ippserver_network_connect_sta) {
			if (is_need_ippserver_reinit_flg) {
				is_need_ippserver_reinit_flg = false;
				vTaskDelay(3000 / portTICK_PERIOD_MS);
				ippserver_start();
			}
		}else {
			if (is_need_ippserver_deinit_flg) {
				is_need_ippserver_deinit_flg = false;
			    ippserver_stop();			
			}
		}
	}

	vTaskDelete(NULL);
}

esp_err_t ippserver_init(void)
{
    uint8_t derived_mac_addr[6] = {0};

	ipp_server_rsp_buf = pp_module_mmu_malloc("ipp_server_rsp_buf", IPP_SERVER_BUF_SIZE_MAX);
	
	ipp_server_info = pp_module_mmu_malloc("ipp_server_info", sizeof(ipp_server_info_t));
	ipp_server_info->instance_name = pp_module_mmu_malloc("instance_name", 48);
	ipp_server_info->host_name = pp_module_mmu_malloc("host_name", 36);
	ipp_server_info->mac = pp_module_mmu_malloc("mac", 18);
	ipp_server_info->url = pp_module_mmu_malloc("url", 48);

    if (ESP_OK == esp_read_mac(&derived_mac_addr[0], ESP_MAC_WIFI_STA)) {
        sprintf(ipp_server_info->mac, "%02x:%02x:%02x:%02x:%02x:%02x", 
			derived_mac_addr[0],derived_mac_addr[1], 
			derived_mac_addr[2],derived_mac_addr[3], 
			derived_mac_addr[4],derived_mac_addr[5]);
    } else {
		strcpy(ipp_server_info->mac, "11:22:33:44:55:66");
	}

	sprintf(ipp_server_info->instance_name, "Paperang "PROJECT_NAME" Series (%02X%02X%02X)",derived_mac_addr[3], 
							derived_mac_addr[4],derived_mac_addr[5]);
	
	sprintf(ipp_server_info->host_name, "PP%02X%02X%02X",derived_mac_addr[3], 
							derived_mac_addr[4],derived_mac_addr[5]);

	ippserver_semap_handle = xSemaphoreCreateCounting(1, 0);
	if (ippserver_semap_handle == NULL) {
		ESP_LOGE(TAG, "ippserver_start: ippserver_semap_handle creat failed");
		return ESP_FAIL;
	}

	if (xTaskCreate(ippserver_task, "ipp_server", 2048, NULL, 4, NULL) != true)
	{
		ESP_LOGE(TAG, "ippserver task creat failed");
		return ESP_FAIL;
	}

    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &network_connect_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &network_disconnect_handler, NULL));
    return ESP_OK;
}

