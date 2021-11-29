#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define GREEN_LED_BRIGHTNESS_FILE "/sys/class/leds/led_green/brightness"
/*
*input parameter: 
*	path:  led node path
*	value: must be "1" or "0"
*return parameter: 
*	<0 failed, >=0 success
*/
int test_write_led(char *path, char const* value)
{
	int fd = 0;
	int ret = 0;
	
	fd = open(path, O_RDWR|O_NOCTTY|O_NDELAY);
	if (fd < 0) {
		printf("%s %d: open failed.\n", __FUNCTION__, __LINE__);
		return -1;
	}
	
	if ((ret = write(fd, value, 1)) <0 ){
		printf("%s: write err, ret=%d\n", __FUNCTION__,ret);
	}
	printf("%s %d: value=%s path=%s\n", __FUNCTION__, __LINE__, value, path);
	close(fd);
	return ret;
}


int main(int argc, char **argv)
{
	test_write_led(GREEN_LED_BRIGHTNESS_FILE, "1");
	sleep(1);
	test_write_led(GREEN_LED_BRIGHTNESS_FILE, "0");
	sleep(1);
	return 0;
}

