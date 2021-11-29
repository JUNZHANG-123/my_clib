#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#define ENABLE_DEBUG_INFO_LOG
#define MODULE_NAME	"my_test"

#ifdef ENABLE_DEBUG_INFO_LOG
#define debug_info(FMT, ...) {\
           char *buf = {0};\
           buf = calloc(strlen(MODULE_NAME)+50, sizeof(char));\
           struct tm *ptm = NULL; \
           time_t o_now = time(NULL);\
           ptm = localtime(&o_now);\
           struct timeval tv;\
           gettimeofday(&tv, NULL);\
           unsigned long long now = (((unsigned long long)tv.tv_sec * 1000000LL) + tv.tv_usec)/100;\
           if (ptm){\
				snprintf(buf, strlen(MODULE_NAME)+50,\
					"[%04d/%02d/%02d %02d:%02d:%02d:%04d %s",\
					ptm->tm_year + 1900,\
					ptm->tm_mon + 1,\
					ptm->tm_mday,\
					ptm->tm_hour,\
					ptm->tm_min,\
					ptm->tm_sec,\
					(int)(now % 10000), MODULE_NAME);\
           } else {\
           		snprintf(buf, strlen(MODULE_NAME)+50, "[%llu:%04d %s",\
						(unsigned long long) now / 10000,\
						(int)(now % 10000), MODULE_NAME);}\
           printf("%s-info]: "FMT, \
           			buf,\
           			##__VA_ARGS__); \
           free(buf);\
}
#else
#define debug_info(FMT, ...)  do {} while(0)
#endif

#define debug_err(FMT, ...) {\
           char *buf = {0};\
           buf = calloc(strlen(MODULE_NAME)+50, sizeof(char));\
           struct tm *ptm = NULL; \
           time_t o_now = time(NULL);\
           ptm = localtime(&o_now);\
           struct timeval tv;\
           gettimeofday(&tv, NULL);\
           unsigned long long now = (((unsigned long long)tv.tv_sec * 1000000LL) + tv.tv_usec)/100;\
           if (ptm){\
				snprintf(buf, strlen(MODULE_NAME)+50,\
					"[%04d/%02d/%02d %02d:%02d:%02d:%04d %s",\
					ptm->tm_year + 1900,\
					ptm->tm_mon + 1,\
					ptm->tm_mday,\
					ptm->tm_hour,\
					ptm->tm_min,\
					ptm->tm_sec,\
					(int)(now % 10000), MODULE_NAME);\
           } else {\
           		snprintf(buf, strlen(MODULE_NAME)+50, "[%llu:%04d %s",\
						(unsigned long long) now / 10000,\
						(int)(now % 10000), MODULE_NAME);}\
           printf("%s-err]: "FMT, \
           			buf,\
           			##__VA_ARGS__); \
           free(buf);\
}


int main(int argc, char **argv)
{
#define OUTPUT_TO_CONSOLE

#ifdef OUTPUT_TO_CONSOLE
	//FILE *fp = NULL;
//开发板使用，ubuntu下使用不仅无效反而会影响输出
/* 	if ((fp = freopen("/dev/console", "w", stdout)) < 0){
		return -1;
	}  */
#else
	FILE *fp = NULL;
	
//重定向到文件
	if ((fp = freopen("log.txt", "w", stdout)) < 0){
		return -1;
	}
#endif

	debug_info("hello log\n");
	debug_err("hello log\n");

#ifdef OUTPUT_TO_CONSOLE
#else
	fclose(fp);
#endif
	return 0;
}


