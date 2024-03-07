#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>


#define PORT            6000
#define BUFF_SIZE       2048
#define MAX_CLIENTS     3


static pthread_t     pp_tcp_thread;
#define HERE() printf("\033[41;30m[%s:%d]\033[0m\n", __FILE__, __LINE__)


void *pp_tcp_server_thread(void* arg)
{
    int i, maxi, maxfd, listenfd, connfd, sockfd;
    int nready , client[MAX_CLIENTS];
    ssize_t n, ret;
    fd_set rset , allset;
    char buf[BUFF_SIZE];
    socklen_t clilen;
    struct sockaddr_in servaddr , cliaddr;

    /*(1) 得到监听描述符*/
    listenfd = socket(AF_INET , SOCK_STREAM , 0);

    int optval = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        perror("setsockopt failed");
        close(listenfd);
        goto EXIT;
    }

    /*(2) 绑定套接字*/
    bzero(&servaddr , sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    bind(listenfd , (struct sockaddr *)&servaddr , sizeof(servaddr));

    /*(3) 监听*/
    listen(listenfd , MAX_CLIENTS);

    /*(4) 设置select*/
    maxfd = listenfd;
    maxi = -1;
    for(i=0 ; i<MAX_CLIENTS ; ++i)
    {
        client[i] = -1;
    }
    FD_ZERO(&allset);
    FD_SET(listenfd , &allset);

    /*(5) 进入服务器接收请求死循环*/
    while(1)
    {
        rset = allset;
        nready = select(maxfd+1 , &rset , NULL , NULL , NULL);
        
        if(FD_ISSET(listenfd , &rset))
        {
            /*接收客户端的请求*/
            clilen = sizeof(cliaddr);
            
            printf("\naccpet connection~\n");

            if((connfd = accept(listenfd , (struct sockaddr *)&cliaddr , &clilen)) < 0)
            {
                perror("accept error.\n");
                goto EXIT;
            }

            printf("accpet a new client: %s:%d\n", inet_ntoa(cliaddr.sin_addr) , cliaddr.sin_port);

            /*将客户链接套接字描述符添加到数组*/
            for(i=0 ; i<MAX_CLIENTS ; ++i)
            {
                if(client[i] < 0)
                {
                    client[i] = connfd;
                    break;
                }
            }

            if(MAX_CLIENTS == i)
            {
                perror("too many connection.\n");
                goto EXIT;
            }

            FD_SET(connfd , &allset);
            if(connfd > maxfd)
                maxfd = connfd;
            if(i > maxi)
                maxi = i;

            if(--nready < 0)
                continue;
        }

        for(i=0; i<=maxi ; ++i)
        {
            if((sockfd = client[i]) < 0)
                continue;
            
            if(FD_ISSET(sockfd , &rset))
            {
                /*处理客户请求*/
                printf("\nreading the socket~~~ \n");
                
                bzero(buf, BUFF_SIZE);
                if((n = read(sockfd , buf , BUFF_SIZE)) <= 0)
                {
                    close(sockfd);
                    FD_CLR(sockfd , &allset);
                    client[i] = -1;
                }
                else {
                    printf("clint[%d] send message: %s\n", i , buf);
                    if((ret = write(sockfd , buf , n)) != n)    
                    {
                        printf("error writing to the sockfd!\n");
                        break;
                    }
                }
                
                if(--nready <= 0)
                    break;
            }
        }
    }

EXIT:
    pthread_exit(NULL);
    return NULL;
}

int pp_tcp_server_create(void)
{
    int error = pthread_create(&pp_tcp_thread, NULL, &pp_tcp_server_thread, NULL);
    if (error != 0) {
        fprintf(stderr, "Cannot create pp_tcp_thread thread: %s", strerror(error));
        return -1;
    }

    return 0;
}



