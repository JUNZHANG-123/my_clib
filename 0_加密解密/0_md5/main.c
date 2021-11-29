#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

void md5_verifyfile(char *filepath,unsigned char *md5_result)
{
    MD5_CTX ctx;
    FILE * fp = NULL;
	int len = 0;
	char buffer[1024] = {0};
	unsigned char tmp_buf[50] = {0};
	
	fp = fopen(filepath,"rb");
	if(fp == NULL) {
		printf("%d Can't open file\n", __LINE__);
		return;
	}

    MD5_Init(&ctx);
    while( (len = fread(buffer, 1, 1024, fp)) > 0 ) {
        MD5_Update(&ctx, buffer, len);
        memset(buffer, 0, sizeof(buffer));
    }
    MD5_Final(tmp_buf,&ctx);

	sprintf((char*)md5_result, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", 
		  tmp_buf[0],tmp_buf[1],tmp_buf[2],tmp_buf[3],tmp_buf[4],
		  tmp_buf[5],tmp_buf[6],tmp_buf[7],tmp_buf[8],tmp_buf[9],
		  tmp_buf[10],tmp_buf[11],tmp_buf[12],tmp_buf[13],tmp_buf[14],
		  tmp_buf[15]);
}

void md5_verifydata(unsigned char *data, int len,unsigned char *md5_result)
{
    MD5_CTX ctx;
	unsigned char tmp_buf[50] = {0};

	MD5_Init(&ctx);

	MD5_Update(&ctx,  data,  len);
	
	MD5_Final(tmp_buf, &ctx);
	
	sprintf((char*)md5_result, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", 
		  tmp_buf[0],tmp_buf[1],tmp_buf[2],tmp_buf[3],tmp_buf[4],
		  tmp_buf[5],tmp_buf[6],tmp_buf[7],tmp_buf[8],tmp_buf[9],
		  tmp_buf[10],tmp_buf[11],tmp_buf[12],tmp_buf[13],tmp_buf[14],
		  tmp_buf[15]);
}

int main(int argc, char **argv)
{
	unsigned char md5_result[32+1] = {0};

#if 0	
	md5_verifyfile("./test", md5_result);
#else
	unsigned char data[] = "12345678";
	md5_verifydata(data, strlen((char*)data), md5_result);
#endif
	printf("md5_result=%s\n",md5_result);
	
	return 0;
}


