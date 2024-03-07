#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include<unistd.h>
#include <sys/time.h>
#include <fcntl.h>

#if 0
typedef enum {
	ZYB_GET_WLAN_MAC = 0,

} zyb_popen_cmd_t;


typedef struct {
	zyb_popen_cmd_t			cmd;
	char					cmd_s[256];
	char					rsp_s[256];
} zyb_popen_data_t;

static zyb_popen_data_t zyb_popen_cmd_list[] = {
	{ZYB_GET_WLAN_MAC, "cat /sys/class/net/wlan0/address", },

};
#endif

int zyb_check_cmd_already_executed(char *cmd)
{
	char pcmd[512] = {0};
	snprintf(pcmd, sizeof(pcmd), "ps | grep %s | grep -v grep|wc -l", cmd);
	
	FILE *fp = NULL;
	fp = popen(pcmd, "r");
	if (fp == NULL)
	{
		printf("popen error!\n");
		return 1;
	}
	
	char data[10] = {0};
	int cnt = 0;
	fgets(data, sizeof(data), fp);
	cnt = atoi(data);
	//printf("cmd=%s cnt=%d\n", cmd, cnt);
	pclose(fp);
	
	if (cnt)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int zyb_wifi_get_mac(char *mac, int size)
{
	FILE *fp = NULL;
	fp = popen("cat /sys/class/net/wlan0/address", "r");
	if (fp == NULL)
	{
		printf("popen error!\n");
		return 1;
	}
	
	fgets(mac, size, fp);
	pclose(fp);
	
	return 0;
}

int zyb_softap_hostapd_init(void)
{
    system("ifconfig wlan0 up");
	system("ifconfig wlan0 192.168.5.1");
	
	if (zyb_check_cmd_already_executed("hostapd"))
	{
		printf("hostapd already executed\n");
		return 0;
	}

	FILE *fp = NULL;
	fp = popen("hostapd -B /mnt/UDISK/hostapd.conf", "r");
	if (fp == NULL)
	{
		printf("popen error!\n");
		return 1;
	}
	
	char rsp[256];
	while (fgets(rsp, sizeof(rsp), fp) != NULL)
	{
		printf("%s\n", rsp);
	}
	pclose(fp);
	
	if (strstr(rsp, "AP-ENABLED"))
	{
		return 0;
	}
	else
	{
		printf("error log: %s\n", rsp);
		return 1;
	}
}

int zyb_softap_dnsmasq_init(void)
{
	if (access("/var/lib/misc/dnsmasq.leases", F_OK) != 0)
	{
		system("mkdir /var/lib/misc");
		system("touch /var/lib/misc/dnsmasq.leases");
	}

	if (zyb_check_cmd_already_executed("dnsmasq") )
	{
		printf("dnsmasq already executed\n");
		return 0;
	}
	
	FILE *fp = NULL;
	fp = popen("dnsmasq -C /etc/dnsmasq.conf", "r");
	if (fp == NULL)
	{
		printf("popen error!\n");
		return 1;
	}
	
	char rsp[256] = {0};
	fgets(rsp, sizeof(rsp), fp);
	pclose(fp);
	
	printf("%s %ld\n", rsp, strlen(rsp));
	return 0;
}

int zyb_wifi_cmd_set(char *cmd, char *cmd_rsp)
{
	//printf("%s cmd=%s cmd_rsp=%s\n", __func__, cmd, cmd_rsp);
	
	FILE *fp = NULL;
	fp = popen(cmd, "r");
	if (fp == NULL)
	{
		printf("popen error!\n");
		return 1;
	}
	
	char rsp[256];
	while (fgets(rsp, sizeof(rsp), fp) != NULL)
	{
		printf("%s\n", rsp);
	}
	pclose(fp);
	
	if (strstr(rsp, cmd_rsp))
	{
		return 0;
	}
	else
	{
		printf("error log: %s\n", rsp);
		return 1;
	}
}

int zyb_hostapd_cli_init(void)
{
	char mac[100] = {0};
	zyb_wifi_get_mac(mac, sizeof(mac));
	printf("mac=%s\n", mac);

	char cmd[128] = {0};
	snprintf(cmd, sizeof(cmd), "hostapd_cli set ssid ZB02_%s", &mac[9]);
	
	if (zyb_wifi_cmd_set(cmd, "OK") )
	{
		printf("%s cmd=%s set error\n", __func__, cmd);
		return 1;
	}
	else
	{
		if (zyb_wifi_cmd_set("hostapd_cli reload", "OK") )
		{
			printf("%s cmd=%s reload error\n", __func__, cmd);
			return 1;
		}
	}
	return 0;
}

int zyb_save_local_hostapd_conf_file(void)
{
	if (access("/mnt/UDISK/hostapd.conf", F_OK) == 0)
	{
		return 0;
	}
	
	system("cp /etc/wifi/hostapd.conf /mnt/UDISK/hostapd.conf");
	
	char mac[100] = {0};
	zyb_wifi_get_mac(mac, sizeof(mac));
	printf("mac=%s\n", mac);

	char cmd[256] = {0};
	snprintf(cmd, sizeof(cmd), "sed -i '3c ssid=ZB02_%s' /mnt/UDISK/hostapd.conf", &mac[9]);
	system(cmd);
	return 0;
}

int zyb_softap_deinit(void)
{
	system("ifconfig wlan0 down");
	return 0;
}

int zyb_softap_reinit(void)
{
	system("ifconfig wlan0 up");
	return 0;
}

int main()
{
	zyb_save_local_hostapd_conf_file();
	zyb_softap_deinit();
	
	long delta_t = 0;
	struct timeval t1, t2;
	gettimeofday(&t1, NULL);
	zyb_softap_hostapd_init();
	
	gettimeofday(&t2, NULL);
	delta_t = (t2.tv_sec-t1.tv_sec) * 1000000 + t2.tv_usec-t1.tv_usec;
	printf("hostapd total time=%ld\n", delta_t);
	
	gettimeofday(&t1, NULL);
	zyb_softap_dnsmasq_init();
	
	gettimeofday(&t2, NULL);
	delta_t = (t2.tv_sec-t1.tv_sec) * 1000000 + t2.tv_usec-t1.tv_usec;
	printf("dnsmasq total time=%ld\n", delta_t);
	
	zyb_softap_deinit();
	gettimeofday(&t1, NULL);
	zyb_softap_reinit();
	gettimeofday(&t2, NULL);
	delta_t = (t2.tv_sec-t1.tv_sec) * 1000000 + t2.tv_usec-t1.tv_usec;
	printf("reinit total time=%ld\n", delta_t);
	
	
	FILE *fp = NULL;
	printf("%d\n", __LINE__);
	fp = popen("zyb_test", "r");
	printf("%d\n", __LINE__);
	if (fp == NULL)
	{
		printf("popen error!\n");
		return 1;
	}
	
	char buffer[256];
    while (!feof(fp)) {
        if (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }
    }
	pclose(fp);
	
	printf("end\n");
	return 0;
}




