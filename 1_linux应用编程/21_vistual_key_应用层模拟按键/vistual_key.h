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
#ifndef __VISTUAL_KEY_H__  
#define __VISTUAL_KEY_H__  
#include <string.h>  
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <linux/input.h>  
#include <linux/uinput.h>  
#include <sys/time.h>  
#include <unistd.h>  
#include <errno.h>   
static void kbdms_open_dev();  
static int kbdms_init_dev(char *dev);  
extern void kbdms_close_dev(void); /* you can call the function explicitly if you no need the function anymore*/  
/* only the following functions which you can called, we initialise the device when you call the following function firstly */  
/* key_code: referce to linux/input.h 
   is_pressed_or_release: 1 if the key is pressed , 0 :release 
   注意按键有按下，就必然会有释放，如果没有释放，再次调用按下函数是没有反映的 
*/  
extern void kbdms_send_button_event(unsigned short key_code, int is_pressed_or_release);  
/* is_rel:1--relative move, else--absolutely 
   if you want to send left or right mouse button , please call kbdms_send_button_event 
*/  
//extern void kbdms_send_mouse_move_events(unsigned short is_rel, unsigned short pos_x, unsigned short pos_y);   
extern void kbdms_send_mouse_move_events(unsigned short is_rel, short pos_x, short pos_y);  
extern void kbdms_send_wheel_events(short wheel_value);  
#endif  /* __VISTUAL_KEY_H__ */ 