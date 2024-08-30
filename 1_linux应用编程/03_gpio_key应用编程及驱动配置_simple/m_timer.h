#ifndef __M_TIMER_H__
#define __M_TIMER_H__
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <pthread.h>


#define TIMER_UNIT_SEC	1

typedef struct timer_handle {
	int interval;
	int elapse; /* 0~interval */
	void* (*timeout_cb)(void* arg);
	/* Special attention should be paid to passing in 
	 * parameters. Global variables are recommended 
	 * Otherwise it is easy to have a wild pointer or a null pointer.
	 */
	char *arg_data;
	int arg_len;
	struct timer_handle *next;
}timer_handle_t;

/* success, return 0; failed, return -1 */
int multi_timer_start(int interval, timer_handle_t *handle, void *arg, int arg_len);
/* success, return 0; failed, return -1 */
int multi_timer_stop(timer_handle_t *handle);

#endif

