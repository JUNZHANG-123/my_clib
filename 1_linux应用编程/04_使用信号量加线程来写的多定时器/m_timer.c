#include "m_timer.h"

typedef struct timer_manage {
	timer_handle_t* head_handle;

    void (* old_sigfunc)(int);
    void (* new_sigfunc)(int);
    struct itimerval value;
	struct itimerval ovalue;
}timer_manage_t;

static timer_manage_t timer_manage;
	
static void timer_ticks_cb(int signo);
static int multi_timer_get_cnt(void);

/* success, return 0; failed, return -1 */
static int multi_timer_init(void)
{
    int ret;
    
    memset(&timer_manage, 0, sizeof(timer_manage_t));
    if( (timer_manage.old_sigfunc = signal(SIGALRM, timer_ticks_cb)) == SIG_ERR) {
        return (-1);
    }
	
    timer_manage.new_sigfunc = timer_ticks_cb;
    
	//Timeout to run first time
    timer_manage.value.it_value.tv_sec = 1;
    timer_manage.value.it_value.tv_usec = 0;
	
	//After first, the Interval time for clock
    timer_manage.value.it_interval.tv_sec = TIMER_UNIT_SEC;
    timer_manage.value.it_interval.tv_usec = 0;
    ret = setitimer(ITIMER_REAL, &timer_manage.value, &timer_manage.ovalue);

    return (ret);
}

/* success, return 0; failed, return -1 */
static int multi_timer_destroy(void)
{
    int ret;
    
    if( (signal(SIGALRM, timer_manage.old_sigfunc)) == SIG_ERR) {
        return (-1);
    }

    ret = setitimer(ITIMER_REAL, &timer_manage.ovalue, &timer_manage.value);
    if(ret < 0) {
        return (-1);
    }

	timer_handle_t* target;
	for(target=timer_manage.head_handle; target; target=target->next) {
		if(timer_manage.head_handle->arg_len > 0) {
			free(timer_manage.head_handle->arg_data);
		}
	}	
	
    memset(&timer_manage, 0, sizeof(timer_manage_t));
	
    return(0);
}

/* success, return 0; failed, return -1 */
int multi_timer_start(int interval, timer_handle_t *handle, void *arg, int arg_len)
{
    if(handle == NULL || interval <= 0 || handle->timeout_cb == NULL) {
        return (-1);
    }
	
	if (multi_timer_get_cnt() == 0){
		multi_timer_init();
	}
	
	timer_handle_t *target = timer_manage.head_handle;
	while(target) {
		if(target == handle){
			printf("multi_timer_start: timer exit\n");
			goto EXIT;
		}	
		target = target->next;
	}
	handle->next = timer_manage.head_handle;
	timer_manage.head_handle = handle;

EXIT:
	if((arg != NULL) && (arg_len > 0)) {
		timer_manage.head_handle->arg_data = (char *)malloc(arg_len);
		memcpy(timer_manage.head_handle->arg_data, arg, arg_len);
		timer_manage.head_handle->arg_len = arg_len;
	}
	timer_manage.head_handle->interval = interval;
	timer_manage.head_handle->elapse = 0;

    return 0;
}

/* returns the number of started timers */
static int multi_timer_get_cnt(void)
{
	int timer_cnt = 0;
	
	timer_handle_t* target;
	for(target=timer_manage.head_handle; target; target=target->next) {
		timer_cnt++;
	}
	//printf("timer_cnt=%d\n", timer_cnt);
	return timer_cnt;
}

/* success, return 0; failed, return -1 */
int multi_timer_stop(timer_handle_t *handle)
{
    if(handle == NULL){
        return (-1);
    }
    
	int timer_cnt = 0;
	timer_handle_t** curr;

	for(curr = &timer_manage.head_handle; *curr; ) {
		timer_handle_t* entry = *curr;
		timer_cnt++;
		if (entry == handle) {
			*curr = entry->next;
			if (entry->arg_len > 0)
				free(entry->arg_data);
		} else {
			curr = &entry->next;
		}	
	}

	/* All timers have been deleted. Stop the base timer */
	if (multi_timer_get_cnt() == 0) {
		multi_timer_destroy();
	}

    return (0);
}

static void timer_ticks_cb(int signo)
{
	timer_handle_t* target;
	printf("%s %d: e.\n", __FUNCTION__, __LINE__);
	for(target=timer_manage.head_handle; target; target=target->next) {
		target->elapse++;
		
		if (target->elapse == target->interval){
			target->elapse = 0;
			if (target->timeout_cb != NULL){
				pthread_t thread;
				struct sched_param param;
				pthread_attr_t attr;
				pthread_attr_init( &attr );
				pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
				pthread_attr_setschedpolicy(&attr, SCHED_RR);
				param.sched_priority = 4;
				pthread_attr_setschedparam(&attr, &param);
				pthread_create(&thread, 
					&attr, target->timeout_cb, (void*)target->arg_data);
				pthread_attr_destroy(&attr);
			}	
		}
	}
}


#if 0
timer_handle_t timer1;
timer_handle_t timer2;
timer_handle_t timer3;

static void get_format_time(char *tstr)
{
    time_t t;
    
    t = time(NULL);
    strcpy(tstr, ctime(&t));
    tstr[strlen(tstr)-1] = '\0';
    
    return;
}


int timer_proc1(void *arg, int len)
{
    static int i = 0;
	
    printf("%s: enter. i = %d\n", __FUNCTION__, i);

    if (i++ == 10){
		printf("%s: delete. i = %d\n", __FUNCTION__, i);
		multi_timer_stop(&timer1);
	}
    return (1);
}

int timer_proc2(void * arg, int len)
{
    static int i = 0;
	
    printf("%s: enter. i = %d\n", __FUNCTION__, i);

    if (i++ == 10){
		printf("%s: delete. i = %d\n", __FUNCTION__, i);
		multi_timer_stop(&timer2);
	}
	
    return (1);
}

int timer_proc3(void * arg, int len)
{
    static int i = 0;
	
    printf("%s: enter. i = %d\n", __FUNCTION__, i);

    if (i++ == 10){
		printf("%s: delete. i = %d\n", __FUNCTION__, i);
		multi_timer_stop(&timer3);
	}
    return (1);
}


int main(void)
{
    char arg[50];
    char tstr[200];
    int ret;
    
    multi_timer_init();
	

	timer1.timeout_cb = timer_proc1;
    ret = multi_timer_start(1, &timer1, NULL, 0);
    printf("ret1=%d\n", ret);
	
	
	timer2.timeout_cb = timer_proc2;
    ret = multi_timer_start(3, &timer2, NULL, 0);
    printf("ret2=%d\n", ret);

	
	timer3.timeout_cb = timer_proc3;	
    ret = multi_timer_start(3, &timer3, NULL, 0);
	
    printf("ret3=%d\n", ret);
	
    while(1) {
		sleep(1);
		if (multi_timer_get_cnt() == 0){
			sleep(10);
			timer1.timeout_cb = timer_proc1;
			ret = multi_timer_start(5, &timer1, NULL, 0);
			printf("ret1=%d\n", ret);	
			
		}
    }
    
    return 0;
}
#endif

