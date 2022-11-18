#include "event_queue.h"


#define TAG		"[event_queue]"

static event_queue_node_t *event_queue_header[EVENT_PRIORITY_NUM_MAX] = {NULL};

void event_queue_msg_push(event_drive_msg_data_t *drive_msg)
{
	int priority = drive_msg->drive_data.priority;
	
	if (event_queue_header[priority] == NULL){
		//第一个节点先加入header，next节点指向null
		event_queue_header[priority] = (event_queue_node_t*)malloc(sizeof(event_queue_node_t));	
		event_queue_header[priority]->drive_msg_data.drive_data.mod        = drive_msg->drive_data.mod;
		event_queue_header[priority]->drive_msg_data.drive_data.event_type = drive_msg->drive_data.event_type;
		event_queue_header[priority]->drive_msg_data.drive_data.status     = drive_msg->drive_data.status;
		event_queue_header[priority]->drive_msg_data.drive_data.priority   = drive_msg->drive_data.priority;
		
		if ((drive_msg->msg_buf != NULL) && (drive_msg->msg_len != 0) ) {
			event_queue_header[priority]->drive_msg_data.msg_buf = (unsigned char*)calloc(1, drive_msg->msg_len+1);
			event_queue_header[priority]->drive_msg_data.msg_len = drive_msg->msg_len;
			memcpy(event_queue_header[priority]->drive_msg_data.msg_buf, drive_msg->msg_buf, drive_msg->msg_len);				
		}

		event_queue_header[priority]->next = NULL;
	} else {
		//第二个节点开始
		event_queue_node_t *p = event_queue_header[priority], *q = NULL;

		//先找到当前最后一个节点（不是空节点）
		while(p->next != NULL)
			p = p->next;

		q = p;//先把当前最后一个节点赋值给q
		p = p->next;//将p指向p->next(此时为空节点)
		p = (event_queue_node_t*)malloc(sizeof(event_queue_node_t));//给p分配空间，并赋值
		p->drive_msg_data.drive_data.mod 		 = drive_msg->drive_data.mod;
		p->drive_msg_data.drive_data.event_type  = drive_msg->drive_data.event_type;
		p->drive_msg_data.drive_data.status 	 = drive_msg->drive_data.status;
		p->drive_msg_data.drive_data.priority 	 = drive_msg->drive_data.priority;
		
		if ((drive_msg->msg_buf != NULL) && (drive_msg->msg_len != 0) ) {
			p->drive_msg_data.msg_buf = (unsigned char*)calloc(1, drive_msg->msg_len+1);
			p->drive_msg_data.msg_len = drive_msg->msg_len;
			memcpy(p->drive_msg_data.msg_buf, drive_msg->msg_buf, drive_msg->msg_len);				
		}		

		p->next = NULL;
		
		q->next = p;//将p 接入链表最后一个节点
	}
	LOGI(TAG, "mod:%d type:%d add now!", drive_msg->drive_data.mod, drive_msg->drive_data.event_type);
}

void event_queue_msg_pop(event_drive_msg_data_t *drive_msg)
{
	int i = 0;

	for (i = 0; i < EVENT_PRIORITY_NUM_MAX; i++) {
		event_queue_node_t *p = event_queue_header[i];
		
		//先进先出，所以每次都出头节点
		if (p == NULL){
			continue;
		} else {	
			event_queue_header[i] = event_queue_header[i]->next;
			
			drive_msg->drive_data.mod 		 = p->drive_msg_data.drive_data.mod;
			drive_msg->drive_data.event_type = p->drive_msg_data.drive_data.event_type;
			drive_msg->drive_data.status 	 = p->drive_msg_data.drive_data.status;
			drive_msg->drive_data.priority 	 = p->drive_msg_data.drive_data.priority;

			if ((p->drive_msg_data.msg_buf != NULL) && (p->drive_msg_data.msg_len != 0) ) {
				drive_msg->msg_buf = (unsigned char*)calloc(1, p->drive_msg_data.msg_len+1);
				drive_msg->msg_len = p->drive_msg_data.msg_len;
				memcpy(drive_msg->msg_buf, p->drive_msg_data.msg_buf, p->drive_msg_data.msg_len);
				
				LOGI(TAG, "MSG=%p", drive_msg->msg_buf);
				
				free(p->drive_msg_data.msg_buf);
				p->drive_msg_data.msg_buf = NULL;
			}			
				
			free(p);
			p = NULL;
			return;		
		}		
	}
}

void event_queue_printf(void)
{
	int i = 0;
	event_queue_node_t *p = NULL;
	
	for (i = 0; i < EVENT_PRIORITY_NUM_MAX; i++) {	
		p = event_queue_header[i];

		while(p != NULL){
			LOGI(TAG, "event_queue_node_print: priority=%d mod=%d event_type=%d status=%d", 
							i,
							p->drive_msg_data.drive_data.mod, 
							p->drive_msg_data.drive_data.event_type,
							p->drive_msg_data.drive_data.status);

			p = p->next;
		}				
	}
}





