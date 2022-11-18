#ifndef __EVENT_DRIVE_H__
#define __EVENT_DRIVE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include "log_general.h"

typedef void (*event_func)(unsigned char *msg_buf, unsigned int msg_len);

typedef enum {
	MODULE_A,
	MODULE_B
}event_module_type_t;

typedef enum {
	EVENT_NONE,
	EVENT_A,
	EVENT_B
}event_type_t;

typedef enum {
	STATUS_A,
	STATUS_B
}event_status_t;

typedef enum {
	PRIORITY_0 = 0,		//高优先级
	PRIORITY_1,
	PRIORITY_2,
	PRIORITY_3,		
	PRIORITY_4,
	PRIORITY_5,		    //低优先级
}event_priority_t;
#define EVENT_PRIORITY_NUM_MAX		(6)		//优先级等级个数

typedef struct {
	event_module_type_t		mod;			//消息的发送模块
	event_type_t    		event_type;		//消息类型
	event_status_t			status;			//自身状态
	event_priority_t		priority;		//优先级
}event_drive_data_t;

typedef struct {
	event_drive_data_t		drive_data;  
	unsigned char			*msg_buf;
	unsigned int			msg_len;
}event_drive_msg_data_t;

typedef struct event_drive_node{
	event_drive_msg_data_t		drive_msg_data;
	struct event_drive_node 	*next;
}event_queue_node_t;

typedef struct {
	event_drive_data_t    drive_data;
	event_func		      func_ptr;
}event_drive_t;

void event_proc(void);




#endif



