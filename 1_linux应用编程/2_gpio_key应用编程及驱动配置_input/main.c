#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/input.h>
#include "../common/m_timer.h"
#include "../common/common.h"

#undef MODULE_NAME
#define MODULE_NAME "app_key"

#define KEY_LONG_PRESS_TIMES 3

timer_handle_t app_key_longpress_timer_handle;
void app_key_stop_longpress_timer(void);

void* app_key_longpress_timeout_task(void *arg)
{
	debug_info("%s %d: e\n", __FUNCTION__, __LINE__);

	app_key_stop_longpress_timer();

	system("reboot");
	return NULL;
}

void app_key_stop_longpress_timer(void)
{
	//debug_info("%s %d: e\n", __FUNCTION__, __LINE__);

	multi_timer_stop(&app_key_longpress_timer_handle);
}

void app_key_start_longpress_timer(void)
{
	//debug_info("%s %d: e.\n", __FUNCTION__, __LINE__);

	app_key_longpress_timer_handle.timeout_cb = app_key_longpress_timeout_task;
	multi_timer_start(KEY_LONG_PRESS_TIMES, &app_key_longpress_timer_handle, NULL, 0);
}

int main(int argc, char **argv)
{
	int fd;
	int ret;
	int key_value = 0;
	
	fd = open("/dev/gpio_key", O_RDONLY);
	if (fd < 0) {
		debug_err("open file failed\n");
		exit(1);
	}
 
	while (1) {
		ret = read(fd, &key_value, 4);
		if (ret < 0) {
			debug_info("read event error!\n");
			exit(1);
		}
		
		if (key_value == 1){
			app_key_start_longpress_timer();
		} else if (key_value == 0) {
			app_key_stop_longpress_timer();
		}
	}
	
	return 0;
}
