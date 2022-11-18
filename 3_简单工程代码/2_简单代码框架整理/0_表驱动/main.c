#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>

typedef void (*event_func)(void *buf);

typedef enum {
	MODULE_A,
	MODULE_B
}module_type_t;

typedef enum {
	EVENT_A,
	EVENT_B
}event_type_t;

typedef enum {
	STATUS_A,
	STATUS_B
}event_status_t;

typedef struct {
	module_type_t	mod;			//消息的发送模块
	event_type_t    event_type;		//消息类型
	event_status_t	status;			//自身状态	
}event_drive_data_t;

typedef struct {
	event_drive_data_t    drive_data;
	event_func		      func_ptr;		//此状态下的处理函数指针
}event_drive_t;

void test1(void *buf)
{
	printf("test1\n");
}

void test2(void *buf)
{
	printf("test2\n");
}

static event_drive_t  event_dirve[] = {
	{{MODULE_A, EVENT_A, STATUS_A}, test1},
	{{MODULE_B, EVENT_A, STATUS_A}, test2},
};

void event_proc(event_drive_data_t *data, void *buf)
{
	int type_num = sizeof(event_dirve)/sizeof(event_drive_t);
	int i = 0;
	
	for (i = 0; i < type_num; i++)
	{
		if ( (data->mod == event_dirve[i].drive_data.mod) && 
			 (data->event_type == event_dirve[i].drive_data.event_type) &&
			 (data->status == event_dirve[i].drive_data.status) )
		{
			event_dirve[i].func_ptr(buf);
		}
	}
}

int main(void)
{
	event_drive_data_t  event_a = {.mod = MODULE_A,
                              .event_type = EVENT_A,
							  .status = STATUS_A,};
	
	event_proc(&event_a, NULL);


	return 0;
}
