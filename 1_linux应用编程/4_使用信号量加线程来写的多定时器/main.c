#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/input.h>
#include "m_timer.h"

#define TEST1_TICK 3

timer_handle_t test1_timer_handle;
void test1_stop_timer(void);

void* test1_timeout_task(void *arg)
{
	printf("%s %d: e\n", __FUNCTION__, __LINE__);

	test1_stop_timer();

	return NULL;
}

void test1_stop_timer(void)
{
	printf("%s %d: e\n", __FUNCTION__, __LINE__);

	multi_timer_stop(&test1_timer_handle);
}

void test1_start_timer(void)
{
	printf("%s %d: e.\n", __FUNCTION__, __LINE__);

	test1_timer_handle.timeout_cb = test1_timeout_task;
	multi_timer_start(TEST1_TICK, &test1_timer_handle, NULL, 0);
}

int main(int argc, char **argv)
{

	test1_start_timer();

	//test1_stop_timer();

	
	return 0;
}
