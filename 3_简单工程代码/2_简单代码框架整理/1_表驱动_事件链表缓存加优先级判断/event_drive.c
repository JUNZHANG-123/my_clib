#include "event_drive.h"
#include "event_queue.h"

#define TAG	    "[event_drive]"

void test1(unsigned char *msg_buf, unsigned int msg_len)
{
	LOGI(TAG, "test1 %s %d", msg_buf, msg_len);
}

void test2(unsigned char *msg_buf, unsigned int msg_len)
{
	LOGI(TAG, "test2 %s %d", msg_buf, msg_len);
}



static event_drive_t  event_dirve[] = {
	{{MODULE_A, EVENT_A, STATUS_A, PRIORITY_0}, test1},
	{{MODULE_B, EVENT_A, STATUS_A, PRIORITY_0}, test2},
};

void event_proc(void)
{
	int type_num = sizeof(event_dirve)/sizeof(event_drive_t);
	int i = 0;
	event_drive_msg_data_t	drive_msg = {.drive_data.event_type = EVENT_NONE,
										 .msg_buf = NULL};
	
	event_queue_msg_pop(&drive_msg);
	if (drive_msg.drive_data.event_type != EVENT_NONE)
	{
		for (i = 0; i < type_num; i++)
		{
			if ( (drive_msg.drive_data.mod == event_dirve[i].drive_data.mod) && 
				 (drive_msg.drive_data.event_type == event_dirve[i].drive_data.event_type) &&
				 (drive_msg.drive_data.status == event_dirve[i].drive_data.status) )
			{
				event_dirve[i].func_ptr(drive_msg.msg_buf, drive_msg.msg_len);
				LOGI(TAG, "MSG=%p", drive_msg.msg_buf);
				if (drive_msg.msg_buf != NULL)
				{
					free(drive_msg.msg_buf);
				}
			}
		}
	}
}





