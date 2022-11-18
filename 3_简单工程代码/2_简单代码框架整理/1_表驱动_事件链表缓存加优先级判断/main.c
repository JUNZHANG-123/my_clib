#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include "event_queue.h"
#include "event_drive.h"
#include "log_general.h"

int main(void)
{
	event_drive_msg_data_t  msg_a = {
							  .drive_data.mod = MODULE_A,
                              .drive_data.event_type = EVENT_A,
							  .drive_data.status = STATUS_A,
							  .drive_data.priority = PRIORITY_1,
							  .msg_buf = (unsigned char*)"msga",
							  .msg_len = 4,
							 };
	
	event_queue_msg_push(&msg_a);
	
	event_drive_msg_data_t  msg_b = {
							  .drive_data.mod = MODULE_B,
                              .drive_data.event_type = EVENT_A,
							  .drive_data.status = STATUS_A,
							  .drive_data.priority = PRIORITY_0,
							  .msg_buf = (unsigned char*)"msgb",
							  .msg_len = 4,
							 };
	
	event_queue_msg_push(&msg_b);
	event_queue_msg_push(&msg_b);
	event_queue_msg_push(&msg_b);
	
	event_queue_printf();
	event_proc();
	event_proc();
	event_proc();
	
	event_queue_printf();
	return 0;
}



