#include "m_timer.h"

timer_handle_t timer1;

void *timer_proc1(void *ptr)
{
    printf("%s: enter\n", __FUNCTION__);
	
	multi_timer_stop(&timer1);
	return NULL;
}

int main(void)
{
	timer1.timeout_cb = timer_proc1;
    multi_timer_start(3, &timer1, NULL, 0);
	printf("%s:%d\n", __FUNCTION__, __LINE__);

	while(1)sleep(1);
	return 0;
}
