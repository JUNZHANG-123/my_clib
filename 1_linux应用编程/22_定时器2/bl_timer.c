#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>
#include "bl_timer.h"


/*macro definition*/
#define MIN_TIMER_ID                   0x00000010
#define MAX_TIMER_ID                   0x0F000000
#define TIMER_UNIT_MS                  10

static void *bl_timer_ticks(void *arg);

/*type struct define*/
typedef struct timer_list_node
{
	struct timer_list_node     *next;
	uint32_t                   repeat_count;	    // 定时器重复次数
	bool                       is_forever_repeat;   // 一直循环
	int                        timer_id;
	uint32_t                   backup_remain_cnt;	// remain_cnt 的备份
	uint32_t                   remain_cnt;			// time tick 转换后 cnt 数
	timeout_cb                 cb;
} timer_list_node_t, *timer_list_node_ptr;

typedef struct timer_list_head_node
{
	int                        valid_node_cnt;			//valid node number in the timer list;
	uint32_t                   last_alloced_id;			//last allocated timer id;
	timer_list_node_ptr        next;
} timer_list_head_node_t, *timer_list_head;

static sem_t *timer_list_sem;
static timer_list_head timer_list;

/*******************************************************************************
* Function name:
* Discription:
* Related documents:
* Parameter:
* Name:   Type            I/O    Discription
*
*
* return:
*
* Modify Time   Modify person      content
* -----------------------------------------------------------------
*******************************************************************************/
void bl_timer_handle(void)
{
	timer_list_node_ptr tmp_ptr, pre_ptr;
	if (sem_wait(timer_list_sem) == -1)
	{
		printf("wait timer list semaphore error! : %s", strerror(errno));
		return;
	}

	//TODO: process timer list
	tmp_ptr = timer_list->next;
	pre_ptr = NULL;
	while (tmp_ptr)
	{
		// 每执行一次遍历所有，并且 remain_cnt 都减一，为0则执行
		if (tmp_ptr->remain_cnt > 0)
		{
			tmp_ptr->remain_cnt--;
		}
		else
		{
			tmp_ptr->remain_cnt = 0;
		}

		if (0 == tmp_ptr->remain_cnt)
		{
			if (tmp_ptr->cb != NULL)
			{
				pthread_t thread;
				struct sched_param param;
				pthread_attr_t attr;
				pthread_attr_init( &attr );
				pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
				pthread_attr_setschedpolicy(&attr, SCHED_RR);
				param.sched_priority = 5;
				pthread_attr_setschedparam(&attr, &param);
				pthread_create(&thread, 
					&attr, tmp_ptr->cb, NULL);
				pthread_attr_destroy(&attr);
			}

			if (!tmp_ptr->is_forever_repeat)
			{
				if (tmp_ptr->repeat_count > 0)
				{
					tmp_ptr->repeat_count--;
				}
				else
				{
					tmp_ptr->repeat_count = 0;
				}
			}

			if (tmp_ptr->is_forever_repeat || tmp_ptr->repeat_count != 0)
			{
				tmp_ptr->remain_cnt = tmp_ptr->backup_remain_cnt;
			}
			else
			{
				/* remove node */
				if (pre_ptr == NULL)
				{
					timer_list->next = tmp_ptr->next;
					tmp_ptr          = timer_list->next;
					timer_list->valid_node_cnt--;
				}
				else
				{
					pre_ptr->next = tmp_ptr->next;
					tmp_ptr       = pre_ptr->next;
					timer_list->valid_node_cnt--;
				}
			}
		}
		else
		{
			pre_ptr = tmp_ptr;
			tmp_ptr = pre_ptr->next;
		}
	}

	if (sem_post(timer_list_sem) == -1)
	{
		printf("post timer list semaphore error!");
		return;
	}
}

int bl_timer_init(void)
{
	/*create timer_list */
	timer_list_sem = sem_open("timerSem", O_CREAT, 0644, 1);
	if (SEM_FAILED == timer_list_sem)
	{
		printf("create timer_list semaphore error, errno = %d!", errno);
		return (-1);

	}

	/*create timer_list */
	timer_list = (timer_list_head)malloc(sizeof (timer_list_head_node_t));
	if (NULL == timer_list)
	{
		printf("Malloc timer list head node error!");
		return (-1);
	}

	timer_list->valid_node_cnt     = 0;
	timer_list->last_alloced_id    = MIN_TIMER_ID;
	timer_list->next               = NULL;

	if (sem_post(timer_list_sem) == -1)
	{
		printf("OspInitTimer:: post timer list semaphore error!");
		free(timer_list);
		return (-1);
	}

	pthread_t pthread_id;
	pthread_attr_t attr;
	struct sched_param param;
	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_RR);
	param.sched_priority = 4;
	pthread_attr_setschedparam(&attr, &param);
	pthread_create(&pthread_id, &attr, bl_timer_ticks, NULL);
	pthread_attr_destroy(&attr);
	return (0);
}

static int bl_timer_insert_node(timer_list_node_ptr node_ptr, int *timer_id)
{
	timer_list_node_ptr tmp_ptr;
	timer_list_node_ptr tmp_ptr1;

	if (sem_wait(timer_list_sem) == -1)
	{
		printf("wait timer list semaphore error! : %s", strerror(errno));
		free(node_ptr);
		*timer_id = 0;
		return (-1);
	}

	//TODO: process timer list
	/*alloc timer id */
	node_ptr->timer_id = timer_list->last_alloced_id + 1;
	*timer_id          = node_ptr->timer_id;
	timer_list->last_alloced_id++;
	if (MAX_TIMER_ID == timer_list->last_alloced_id)
	{
		timer_list->last_alloced_id = MIN_TIMER_ID;
	}

	/*insert timer node to timer list */
	tmp_ptr  = timer_list->next;
	tmp_ptr1 = NULL;
	while (tmp_ptr && ((node_ptr->remain_cnt) > (tmp_ptr->remain_cnt)))
	{
		tmp_ptr1 = tmp_ptr;
		tmp_ptr  = tmp_ptr->next;
	}

	if (NULL == tmp_ptr1)
	{
		node_ptr->next   = tmp_ptr;
		timer_list->next = node_ptr;
		timer_list->valid_node_cnt++;
	}
	else
	{
		node_ptr->next = tmp_ptr;
		tmp_ptr1->next = node_ptr;
		timer_list->valid_node_cnt++;
	}

	if (sem_post(timer_list_sem) == -1)
	{
		printf("post timer list semaphore error!");
		free(node_ptr);
		*timer_id = 0;
		return (-1);
	}

	return (0);
}

int bl_timer_start(int *timer_id, uint32_t repeat_count, uint32_t timeout_ms, timeout_cb cb)
{
	if (cb == NULL || timer_id == NULL)
	{
		printf("param err");
		return -1;
	}
	
	timer_list_node_ptr node_ptr = (timer_list_node_ptr)malloc(sizeof (timer_list_node_t));
	if (NULL == node_ptr)
	{
		printf("timer list node malloc failed!");
		return -1;
	}

	node_ptr->next       = NULL;
	node_ptr->cb         = cb;
	node_ptr->remain_cnt = timeout_ms/TIMER_UNIT_MS;
	if (node_ptr->remain_cnt < 1)
	{
		node_ptr->remain_cnt = 1;
	}

	node_ptr->repeat_count      = repeat_count;
	node_ptr->backup_remain_cnt = node_ptr->remain_cnt;
	node_ptr->is_forever_repeat = node_ptr->repeat_count == BL_FOREVER_REPEAT? true:false;

	return (bl_timer_insert_node(node_ptr, timer_id));
}

int bl_timer_start_once(int *timer_id, uint32_t timeout_ms, timeout_cb cb)
{
	return bl_timer_start(timer_id, 1, timeout_ms, cb);
}

int bl_timer_change(int timer_id, uint32_t timeout_ms, uint32_t repeat_count)
{
	timer_list_node_ptr tmp_ptr;
    int ret = -1;

	if (sem_wait(timer_list_sem) == -1)
	{
		printf("wait timer list semaphore error! : %s", strerror(errno));
		return (-1);
	}

	//TODO: process timer list
	tmp_ptr = timer_list->next;
	while (tmp_ptr && (timer_id != tmp_ptr->timer_id))
	{
		tmp_ptr = tmp_ptr->next;
	}
	
	if (tmp_ptr)
	{
        printf("find timer: %d, change it timeout=%u, repeat_count=%u", timer_id,timeout_ms, repeat_count);
        tmp_ptr->remain_cnt = timeout_ms/TIMER_UNIT_MS;
        if (tmp_ptr->remain_cnt < 1)
        {
            tmp_ptr->remain_cnt = 1;
        }
        tmp_ptr->repeat_count      = repeat_count;
        tmp_ptr->backup_remain_cnt = tmp_ptr->remain_cnt;
        ret = 0;
    }
    else
    {
        printf("failed to find timer: %d", timer_id);
        ret = -1;
    }

    if (sem_post(timer_list_sem) == -1)
    {
        printf("post timer list semaphore error!");
        return (-1);
    }

    return ret;
}

static int bl_timer_del(int *timer_id)
{
	timer_list_node_ptr tmp_ptr;
	timer_list_node_ptr tmp_ptr1;

	if (sem_wait(timer_list_sem) == -1)
	{
		printf("wait timer list semaphore error! : %s", strerror(errno));
		return (-1);
	}

	//TODO: process timer list
	tmp_ptr  = timer_list->next;
	tmp_ptr1 = NULL;
	while (tmp_ptr && (*timer_id != tmp_ptr->timer_id))
	{
		tmp_ptr1 = tmp_ptr;
		tmp_ptr  = tmp_ptr->next;
	}

	if (tmp_ptr)
	{
		if (NULL == tmp_ptr1)
		{
			timer_list->next = tmp_ptr->next;
			free(tmp_ptr);
			timer_list->valid_node_cnt--;
		}
		else
		{
			tmp_ptr1->next = tmp_ptr->next;
			free(tmp_ptr);
			timer_list->valid_node_cnt--;
		}
	}
	else
	{
		printf("failed to find timer: %d", *timer_id);
	}

	*timer_id = -1;
	
	if (sem_post(timer_list_sem) == -1)
	{
		printf("post timer list semaphore error!");
		return (-1);
	}

	return (0);
}

int bl_timer_stop(int *timer_id)
{
	if (*timer_id == -1)
	{
		return 0;
	}

	return bl_timer_del(timer_id);
}

int bl_timer_is_exit(int timer_id)
{
	timer_list_node_ptr tmp_ptr;
	int ret = 1;

	if (timer_id == -1)
	{
		return 0;
	}

	if (sem_wait(timer_list_sem) == -1)
	{
		printf("wait timer list semaphore error! : %s", strerror(errno));
		return 0;
	}

	//TODO: process timer list
	tmp_ptr  = timer_list->next;
	while (tmp_ptr && (timer_id != tmp_ptr->timer_id))
	{
		tmp_ptr  = tmp_ptr->next;
	}
	
	if (tmp_ptr)
	{
		ret = 1;
	}
	else
	{
		ret = 0;
	}

	if (sem_post(timer_list_sem) == -1)
	{
		printf("bl_timer_is_exit:: post timer list semaphore error!");
		return 0;
	}

	return ret;
}

void bl_timer_src_del(void)
{
	sem_close(timer_list_sem);
	sem_unlink("timerSem");
	return;
}

static void *bl_timer_ticks(void *arg)
{
	while (1)
	{
		struct timeval tv;
		tv.tv_sec  = 0;
		tv.tv_usec = TIMER_UNIT_MS*1000;
		select(0, NULL, NULL, NULL, &tv);

		bl_timer_handle();
	}

	return NULL;
}
