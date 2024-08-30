#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define TEST_SN_STR "X312345678"
#define TEST_SN_STR2 "aaaaaaaaaa"
#define TEST_SN_STR3 "BBBBBBBBBB"
#define TEST_KEY_OFFSET 64

int main(int argc, char **argv)
{
	int mtd_fd = 0;
	int len = 0;
	char read_buf[50] = {0};
	
    mtd_fd = open("/dev/mtdblock3", O_TRUNC | O_RDWR);
    if (mtd_fd < 0) {
        printf("Open /dev/mtdblock3 error\n");
    }
	
	lseek(mtd_fd, 0, SEEK_SET);
	
	len = write(mtd_fd, TEST_SN_STR, strlen(TEST_SN_STR));
	printf("write len is %d\n", len);

	lseek(mtd_fd, 0, SEEK_SET);
	len = 0;
	memset(read_buf, 0, sizeof(read_buf));
	len = read(mtd_fd, read_buf, strlen(TEST_SN_STR));
	printf("read len is %d\n", len);
	printf("read read_buf is %s\n", read_buf);
	
	lseek(mtd_fd, 0, SEEK_SET);
	
	len = write(mtd_fd, TEST_SN_STR2, strlen(TEST_SN_STR2));
	printf("write2 len is %d\n", len);

	lseek(mtd_fd, 0, SEEK_SET);
	len = 0;
	memset(read_buf, 0, sizeof(read_buf));
	len = read(mtd_fd, read_buf, strlen(TEST_SN_STR2));
	printf("read2 len is %d\n", len);
	printf("read2 read_buf is %s\n", read_buf);

	lseek(mtd_fd, TEST_KEY_OFFSET, SEEK_SET);
	
	len = write(mtd_fd, TEST_SN_STR3, strlen(TEST_SN_STR3));
	printf("write3 len is %d\n", len);

	lseek(mtd_fd, TEST_KEY_OFFSET, SEEK_SET);
	len = 0;
	memset(read_buf, 0, sizeof(read_buf));
	len = read(mtd_fd, read_buf, strlen(TEST_SN_STR3));
	printf("read3 len is %d\n", len);
	printf("read3 read_buf is %s\n", read_buf);

	lseek(mtd_fd, TEST_KEY_OFFSET*2, SEEK_SET);
	
	len = write(mtd_fd, TEST_SN_STR2, strlen(TEST_SN_STR2));
	printf("write4 len is %d\n", len);

	lseek(mtd_fd, TEST_KEY_OFFSET*2, SEEK_SET);
	len = 0;
	memset(read_buf, 0, sizeof(read_buf));
	len = read(mtd_fd, read_buf, strlen(TEST_SN_STR2));
	printf("read4 len is %d\n", len);
	printf("read4 read_buf is %s\n", read_buf);
						
	return 0;
}

