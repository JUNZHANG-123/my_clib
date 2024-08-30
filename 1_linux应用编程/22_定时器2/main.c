#include <unistd.h>
#include <stdio.h>
#include "bl_timer.h"



void *timer1_cb(void *ptr)
{
    printf("--1--\n");
    return NULL;
}

void *timer2_cb(void *ptr)
{
    printf("--2--\n");
    return NULL;
}

void *timer3_cb(void *ptr)
{
    printf("--3--\n");
    return NULL;
}

int main(int argc, char **argv)
{
    bl_timer_init();

    int timer1, timer2, timer3;
    bl_timer_start(&timer1, BL_FOREVER_REPEAT, 1000, timer1_cb);
    bl_timer_start(&timer2, 3, 1000, timer2_cb);
    bl_timer_start(&timer3, 2, 100, timer3_cb);

    while(1)sleep(1);
    return 0;
}

