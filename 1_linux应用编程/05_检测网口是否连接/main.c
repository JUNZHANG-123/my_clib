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
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>

#define HTTPS_DEFAULT_PORT 443
#define PAPERANG_CLOUD_HOST  "miaocloud.paperang.com"
#define MAX_WAIT_TIME   1
#define MAX_NO_PACKETS  1
#define ICMP_HEADSIZE 8 
#define PACKET_SIZE     50

static char sendpacket[PACKET_SIZE];
static char recvpacket[PACKET_SIZE];
static int sockfd = 0;
static struct sockaddr_in dest_addr = {0}, recv_addr = {0};
static pid_t pid;

static unsigned short cal_chksum(unsigned short *addr,int len)
{       
	int nleft=len;
	int sum=0;
	unsigned short *w=addr;
	unsigned short answer=0;
	
	//把ICMP报头二进制数据以2字节为单位累加起来
	while(nleft>1) {       
		sum+=*w++;
		nleft-=2;
	}

	//若ICMP报头为奇数个字节,会剩下最后一字节.
	//把最后一个字节视为一个2字节数据的高字节,
	//这个2字节数据的低字节为0,继续累加
	if( nleft==1){
		*(unsigned char *)(&answer)=*(unsigned char *)w;
		sum+=answer;
	}
	
	sum=(sum>>16)+(sum&0xffff);
	sum+=(sum>>16);
	answer=~sum;
	return answer;
}

static int pack(int pkt_no,char*sendpacket)
{       
	int packsize;
	struct icmp *icmp;
	struct timeval *tval;
	
	icmp=(struct icmp*)sendpacket;
	icmp->icmp_type=ICMP_ECHO;   //设置类型为ICMP请求报文
	icmp->icmp_code=0;
	icmp->icmp_cksum=0;
	icmp->icmp_seq=pkt_no;
	icmp->icmp_id=pid;			//设置当前进程ID为ICMP标示符
	packsize=ICMP_HEADSIZE+sizeof(struct timeval);
	tval= (struct timeval *)icmp->icmp_data;
	gettimeofday(tval,NULL);
	icmp->icmp_cksum=cal_chksum( (unsigned short *)icmp,packsize); 
	return packsize;
}

static int unpack(int cur_seq,char *buf,int len)
{    
	int iphdrlen;
	struct ip *ip;
	struct icmp *icmp;
	
	ip=(struct ip *)buf;
	iphdrlen=ip->ip_hl<<2;		//求ip报头长度,即ip报头的长度标志乘4
	icmp=(struct icmp *)(buf+iphdrlen);		//越过ip报头,指向ICMP报头
	len-=iphdrlen;		//ICMP报头及ICMP数据报的总长度
	if( len<8)
		return -1;       
	if( (icmp->icmp_type==ICMP_ECHOREPLY) 
		&& (icmp->icmp_id==pid) && (icmp->icmp_seq==cur_seq))
		return 0;	
	else return -1;
}

static int send_packet(int pkt_no,char *sendpacket)
{    
	int packetsize;
	
	packetsize = pack(pkt_no,sendpacket);
	
	if(sendto(sockfd,sendpacket,packetsize,0,
		(struct sockaddr *)&dest_addr,sizeof(dest_addr) )<0){      
		printf("[NetStatus]  error : sendto error\n");
		return -1;
	}
	return 1;
}

static int recv_packet(int pkt_no,char *recvpacket)
{       	
	int n = 0, retry_cnt = 0;
	unsigned int fromlen = 0;
	fd_set rfds;
	
	FD_ZERO(&rfds);
	FD_SET(sockfd,&rfds);
	fromlen = sizeof(recv_addr);

    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
	
	while(retry_cnt < 10) {
		if (select(sockfd+1, &rfds, NULL, NULL, &tv) > 0) {		
			if (FD_ISSET(sockfd,&rfds)) { 
				if( (n=recvfrom(sockfd,recvpacket,
					PACKET_SIZE,0,(struct sockaddr *)&recv_addr, &fromlen)) <0){   
					if(errno == EINTR)
						return -1;
					printf("recvfrom error");
					return -2;
				}		
			} 
			if(unpack(pkt_no,recvpacket,n) == -1)
				continue;
			return 1;
		}
		retry_cnt ++;
	}

	return -1;
}

bool get_network_conn_sta(void)
{
	struct hostent *host = NULL;
	int iFlag = 0;
	
	pid = getpid();
	if((host = gethostbyname(PAPERANG_CLOUD_HOST)) == NULL){
		printf("%s %d: gethostbyname err\n", __FUNCTION__, __LINE__);
		return false;
	}

	memset(&recv_addr, 0, sizeof(recv_addr));
	memset(sendpacket, 0, PACKET_SIZE);
	memset(recvpacket, 0, PACKET_SIZE);
	
	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(HTTPS_DEFAULT_PORT);
	dest_addr.sin_addr = *((struct in_addr *)host->h_addr);	

	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0 ){
		printf("%s %d: creat socket err\n", __FUNCTION__, __LINE__);
		return false;
	}
	
	if((iFlag = fcntl(sockfd, F_GETFL, 0))<0){
		printf("%s %d: fcntl(sockfd,F_GETFL,0) err\n", __FUNCTION__, __LINE__);
		goto EXIT;
	}
	
	iFlag |= O_NONBLOCK;
	if(fcntl(sockfd, F_SETFL, iFlag)<0){
		printf("%s %d: fcntl(sockfd,F_SETFL,iFlag) err\n", __FUNCTION__, __LINE__);
		goto EXIT;
	}
	
	if(send_packet(0, sendpacket) < 0) {
		printf("[NetStatus]  error : send_packet");
		goto EXIT;
	}	

	if(recv_packet(0, recvpacket) > 0) {
		close(sockfd);
		sockfd = 0;
		return true;
	}

EXIT:
	close(sockfd);
	sockfd = 0;
	return false;
}

int main(int argc, char **argv)
{
	while(1) {
		if (!get_network_conn_sta()){
			printf("network disconnect\n");		
		} else {
			printf("network connected\n");
		}
		
		sleep(2);
	}
	return 0;
}

