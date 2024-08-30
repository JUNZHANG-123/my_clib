#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <signal.h>
#include <fcntl.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>


int net_detect(char* net_name)
{
    int skfd = 0;
    struct ifreq ifr;
    struct sockaddr_in *pAddr = NULL;
	
    skfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(skfd < 0) {
        printf("%s:%d Open socket error!\n", __FILE__, __LINE__);
        return -1;
    }
    strcpy(ifr.ifr_name, net_name);
	
    if(ioctl(skfd, SIOCGIFFLAGS, &ifr) <0 ){
        printf("%s:%d IOCTL error!\n", __FILE__, __LINE__);
        printf("Maybe ethernet inferface %s is not valid!", ifr.ifr_name);
        close(skfd);
        return -1;
    }
	
    if(ifr.ifr_flags & IFF_RUNNING) {
        printf("%s is running :)\n", ifr.ifr_name);
    } else {
        printf("%s is not running :(\n", ifr.ifr_name);
    }
    if(ioctl(skfd,SIOCGIFADDR,&ifr)<0)
    {
        printf("SIOCGIFADDR IOCTL error!\n");
        close(skfd);
        return -1;
    }
    pAddr = (struct sockaddr_in *)&(ifr.ifr_addr);
    printf("ip addr :[%s]\n", inet_ntoa(pAddr->sin_addr));
    
    if(ioctl(skfd,SIOCGIFHWADDR,&ifr)<0)
    {
        printf("SIOCGIFHWADDR IOCTL error!\n");
        close(skfd);
        return -1;
    }
	
	#if 1
    printf("mac addr: %02x:%02x:%02x:%02x:%02x:%02x\n",
        (unsigned char)ifr.ifr_hwaddr.sa_data[0],
        (unsigned char)ifr.ifr_hwaddr.sa_data[1],
        (unsigned char)ifr.ifr_hwaddr.sa_data[2],
        (unsigned char)ifr.ifr_hwaddr.sa_data[3],
        (unsigned char)ifr.ifr_hwaddr.sa_data[4],
        (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
	#endif
    close(skfd);
    return 0;
}

int main(int argc, char **argv)
{
	while(1) {
		if (net_detect("eth0") < 0){
			printf("eth0 disconnect\n");		
		} else {
			printf("eth0 connected\n");
		}
		
		sleep(2);
	}
	return 0;
}

