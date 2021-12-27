#ifndef _IPP_SERVER_H_
#define _IPP_SERVER_H_
#include "esp_err.h"


#define IPP_SYSINFO_SN_MAX         (32)
#define IPP_SYSINFO_NAME_MAX       (32)

#define IPP_SYSINFO_BTNAME_MAX     (32)
#define IPP_SYSINFO_BTPIN_MAX      (32)
#define IPP_SYSINFO_BTMACADDR_MAX  (16)

#define IPP_SYSINFO_WIFINAME_MAX   (32)
#define IPP_SYSINFO_WIFIPWD_MAX    (32)
#define IPP_SYSINFO_WIFIMACADDR_MAX  (16)

typedef struct {
    char dev_sn[IPP_SYSINFO_SN_MAX];
    char dev_name[IPP_SYSINFO_NAME_MAX];

    struct BTInfo {
        char name[IPP_SYSINFO_BTNAME_MAX];
        char pin[IPP_SYSINFO_BTPIN_MAX];
        char addr[IPP_SYSINFO_BTMACADDR_MAX];
    } bt_info;

    struct WIFIInfo {
        char name[IPP_SYSINFO_BTNAME_MAX];
        char pwd[IPP_SYSINFO_BTNAME_MAX];
        char addr[IPP_SYSINFO_WIFIMACADDR_MAX];
        char auth;
    } wifi_info;

} IPP_SysInfo_Struct;

typedef struct {
    uint8_t  printername[IPP_SYSINFO_NAME_MAX]; /* printername */
    uint32_t pagesize;     /* Media PageSize list */
    uint32_t mediatype;    /* Media Type list */
    uint32_t dataformat;   /* Media Dataformat list */
    uint32_t connected;    /* 1: connected, 0: disconnected */
    uint32_t inklevel;     /* 0(poor)~100(full) */
    uint8_t  state[128]; /* state */
} IPP_PrinterInfo_Struct;

typedef struct {
    uint32_t jobid[2];     /* printer id from Cloud, 64bits */
    uint8_t  jobstate[128];
} IPP_JobInfo_Struct;

typedef struct {
	char *instance_name;
	char *host_name;
	char *mac;
	char *url;
}ipp_server_info_t;


esp_err_t ippserver_init(void);
esp_err_t paperang_mdns_init(void);
ipp_server_info_t* ipp_get_server_info(void);
int ipp_get_job_id(void);

#endif
