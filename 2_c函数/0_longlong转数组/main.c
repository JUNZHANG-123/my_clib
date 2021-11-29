#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union uuid_data{
    unsigned long long uuid;
	unsigned char uuid_data[8];
}uuid_data_t;

int main(int argc, char **argv)
{
	uuid_data_t uuid;
	
	uuid.uuid = 0x7FFFFFFFFFFFFFFF;

	int i = 0;
	
	for (i = 0; i < 8; i++)
		printf("i=%d, data=0x%02x\n", i, uuid.uuid_data[i]);

	return 0;
}


