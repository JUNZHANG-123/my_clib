/** 
 * @file  The file is using for (>>> function<<<) 
 * @author imxiangpeng 
 * @time   
 * 
 * Copyright (C) imxiangpeng@gmail.com, Inc. All Rights Reserved. 
 * Written by imxiangpeng@gmail.com 
 * 
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * as published by the Free Software Foundation; either version 
 * 2 of the License, or (at your option) any later version. 
 */ 

#include "vistual_key.h"

static int uinput_fd = -1;
static struct uinput_user_dev uinput;
static struct input_event event;
static void kbdms_open_dev() {  
    int ret = -1;  
    ret = kbdms_init_dev("/dev/uinput");  
    if (ret < 0) {  
        ret = kbdms_init_dev("/dev/input/uinput");  
        if(ret < 0){  
          printf("call kbdms_open_dev failure/n");  
          return;  
        }  
    }
}

static int kbdms_init_dev(char *dev) {  
  int i = 0;  
  if(dev == NULL){  
    printf("The device is null/n");  
    return -1;  
  }  
  uinput_fd = open(dev, O_WRONLY | O_NDELAY);  
  if(uinput_fd < 0){  
    perror("open uinput device failure:");  
    return -1;  
  }  
  memset(&uinput, 0, sizeof(uinput));  
  strncpy(uinput.name,"xiangpeng's virtual device",UINPUT_MAX_NAME_SIZE);  
  uinput.id.version = 4;  
  uinput.id.bustype = BUS_USB;  
  ioctl(uinput_fd, UI_SET_EVBIT, EV_KEY);  
  ioctl(uinput_fd, UI_SET_EVBIT, EV_REL);  
  ioctl(uinput_fd, UI_SET_RELBIT, REL_X);  
  ioctl(uinput_fd, UI_SET_RELBIT, REL_Y);  
  ioctl(uinput_fd, UI_SET_RELBIT, REL_WHEEL);  
    
  for(i = 0; i < 256; i++){  
    ioctl(uinput_fd, UI_SET_KEYBIT, i);  
  } /* end for */  
  ioctl(uinput_fd, UI_SET_KEYBIT, BTN_MOUSE);  
  ioctl(uinput_fd, UI_SET_KEYBIT, BTN_TOUCH);  
  ioctl(uinput_fd, UI_SET_KEYBIT, BTN_LEFT);  
  ioctl(uinput_fd, UI_SET_KEYBIT, BTN_MIDDLE);  
  ioctl(uinput_fd, UI_SET_KEYBIT, BTN_RIGHT);  
  ioctl(uinput_fd, UI_SET_KEYBIT, BTN_FORWARD);  
  ioctl(uinput_fd, UI_SET_KEYBIT, BTN_BACK);  
  /* Create input device into input sub-system */  
  write(uinput_fd, &uinput, sizeof(uinput));  
  if(ioctl(uinput_fd, UI_DEV_CREATE)){  
    perror("create uinput device");  
    return -1;  
  }  
  return 0;                     /* success */  
    
} /* end init_uinput_dev function */

/* is_rel:1--relative move, else--absolutely 
   which_button_pressed: 0--no button press, 1--left button press, 2--right button press 3--middle button press 
    
 */  
void kbdms_send_mouse_move_events(unsigned short is_rel, short pos_x, short pos_y){  
  if(uinput_fd <= 0){  
      
    printf("RC : %s please call dbdms_init_dev first/n",__FUNCTION__);  
    kbdms_open_dev();  
    if(uinput_fd <= 0)  
      return;  
  }  
  /* Move pointer to (0,0) location */  
  memset(&event, 0, sizeof(event));  
  gettimeofday(&event.time, NULL);  
  event.type = (is_rel == 1)?EV_REL:EV_ABS;  
  event.code = (is_rel == 1)?REL_X:ABS_X;  
  event.value = pos_x;  
  write(uinput_fd, &event, sizeof(event));    
  event.type = EV_SYN;  
  event.code = SYN_REPORT;  
  event.value = 0;  
  write(uinput_fd, &event, sizeof(event));  
  memset(&event, 0, sizeof(event));  
  gettimeofday(&event.time, NULL);  
  event.type = (is_rel == 1)?EV_REL:EV_ABS;  
  event.code = (is_rel == 1)?REL_Y:ABS_Y;  
  event.value = pos_y;  
  write(uinput_fd, &event, sizeof(event));  
  /* 鼠标点击事件我们也通过 kbdms_send_button_event 来发送*/  
    
} /* end send_click_events function */

/* key_code: referce to linux/input.h 
   is_pressed_or_release: 1 if the key is pressed , 0 :release 
 */  
void kbdms_send_button_event(unsigned short key_code, int is_pressed_or_release){  
    
  if(uinput_fd <= 0){  
    printf("RC : %s please call dbdms_init_dev first/n",__FUNCTION__);  
    kbdms_open_dev();  
    if(uinput_fd <= 0)  
      return;  
  }  
  /* report button click --press event */  
    
  memset(&event, 0, sizeof(event));  
  gettimeofday(&event.time, NULL);  
  event.type = EV_KEY;  
  event.code = key_code;  
  event.value = is_pressed_or_release;  
  write(uinput_fd, &event, sizeof(event));  
  event.type = EV_SYN;  
  event.code = SYN_REPORT;  
  event.value = 0;  
  write(uinput_fd, &event, sizeof(event));  
    
}

void kbdms_send_wheel_events(short wheel_value){  
  if(uinput_fd <= 0){  
    printf("RC : %s please call dbdms_init_dev first/n",__FUNCTION__);  
    kbdms_open_dev();      
    if(uinput_fd <= 0)  
      return;  
     
  }  
  /* Move pointer to (0,0) location */  
  memset(&event, 0, sizeof(event));  
  gettimeofday(&event.time, NULL);  
  event.type = EV_REL;  
  event.code = REL_WHEEL;  
  event.value = wheel_value;  
  write(uinput_fd, &event, sizeof(event));    
  event.type = EV_SYN;  
  event.code = SYN_REPORT;  
  event.value = 0;  
  write(uinput_fd, &event, sizeof(event));  
    
} /* end send_click_events function */ 

void kbdms_close_dev(void){  
  if(uinput_fd > 0){  
    ioctl(uinput_fd, UI_DEV_DESTROY);  
    close(uinput_fd);  
  }  
}  

#if 0                           /* using for test all the functions */   
int main(int argc, char **argv){  
  if(argc <2){  
    printf("Please specified the uinput device path/n");  
    return -1;  
  }  
  printf("The device is :%s/n",argv[1]);  
  if(kbdms_init_dev(argv[1]) < 0){  
    printf("Call init_uinput_dev failure/n");  
    return -1;  
  }  
    
  while(1){  
    printf("we will send a click and a button event/n");  
    //send_click_events();   
    kbdms_send_button_event(KEY_LEFT, 1);  
    kbdms_send_button_event(KEY_LEFT, 0);  
    sleep(3);  
    kbdms_send_button_event(KEY_DOWN,1);  
    kbdms_send_button_event(KEY_DOWN,0);  
    sleep(2);  
    kbdms_send_button_event(KEY_DOWN,1);  
    kbdms_send_button_event(KEY_DOWN,0);  
    sleep(2);  
    printf("we will call kbdms_send_wheel_events/n");  
    kbdms_send_wheel_events(10);  
    printf("We will wheel back up/n");  
    sleep(2);  
      
    kbdms_send_wheel_events(-10);  
  }  
  kbdms_close_dev();  
  return 0;  
}  
#endif 