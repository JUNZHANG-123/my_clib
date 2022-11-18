#ifndef __EVENT_QUEUE_H__
#define __EVENT_QUEUE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include "event_drive.h"
#include "log_general.h"

void event_queue_msg_push(event_drive_msg_data_t *drive_msg);
void event_queue_msg_pop(event_drive_msg_data_t *drive_msg);
void event_queue_printf(void);
#endif