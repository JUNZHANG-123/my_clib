#include "m_timer.h"

timer_handle_t timer1;
timer_handle_t timer2;
timer_handle_t timer3;


void *timer_proc1(void *ptr)
{
	multi_timer_stop(&timer1);		// 放到最前面
	
	printf("%s: enter\n", __FUNCTION__);
	return NULL;
}

void* timer_proc2(void * arg)
{
	multi_timer_stop(&timer2);
	printf("%s: enter\n", __FUNCTION__);
    return NULL;
}

void* timer_proc3(void * arg)
{
	multi_timer_stop(&timer3);
	printf("%s: enter\n", __FUNCTION__);
    return NULL;
}

int main(void)
{
	timer1.timeout_cb = timer_proc1;
	multi_timer_start(3, &timer1, NULL, 0);

	timer2.timeout_cb = timer_proc2;
	multi_timer_start(3, &timer2, NULL, 0);
	printf("%s:%d\n", __FUNCTION__, __LINE__);

	while(1)sleep(1);
	return 0;
}
