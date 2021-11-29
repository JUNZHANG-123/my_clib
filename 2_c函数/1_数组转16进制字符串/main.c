#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
*input parameter: 
*	buf: hex source buf; 
*	buflen: hex source buf lens; 
*	uppercase_flg: true, output uppercase;
*	out: output string buf;
*return parameter: 
*	-1 failed, otherwise the success
*/
int arrayToHexStr(unsigned char *buf, unsigned int buflen, bool uppercase_flg, char *out)
{
    char *strBuf = NULL;
    char *pbuf = NULL;
    int i = 0;

	strBuf = (char*)calloc(buflen*2+1, sizeof(char));
	pbuf = (char*)calloc(buflen*2+1, sizeof(char));
	if (strBuf == NULL || pbuf == NULL)
		return -1;
	
    for(i = 0; i < buflen; i++){
		if (uppercase_flg)
			sprintf(pbuf, "%02X", buf[i]);
		else
			sprintf(pbuf, "%02x", buf[i]);
        strncat(strBuf, pbuf, 2);
    }
    strncpy(out, strBuf, buflen * 2);

	free(strBuf);
	free(pbuf);
	
    return buflen * 2;
}

int main(int argc, char **argv)
{
	unsigned char data[] = {0xaa,0x12,0xf3,0x56};
	char out_data[50] = {0};

	arrayToHexStr(data, sizeof(data), true, out_data);

	printf("out_data=%s\n", out_data);
	return 0;
}


