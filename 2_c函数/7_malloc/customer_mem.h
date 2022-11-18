#ifndef __CUSTOMER_MEM_H__
#define __CUSTOMER_MEM_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16
#define u16 unsigned short
#endif

#ifndef u32
#define u32 unsigned int
#endif

//定义两个内存池
#define SRAMIN 0 //内部内存池
#define SRAMEX 1 //外部内存池

#define SRAMBANK 1 //2	    //定义支持的SRAM块数.

//mem1内存参数设定.mem1完全处于内部SRAM里面.
#define MEM1_BLOCK_SIZE 32                                    //内存块大小为32字节
#define MEM1_MAX_SIZE (9 * 1024)                              //最大管理内存 40K
#define MEM1_ALLOC_TABLE_SIZE MEM1_MAX_SIZE / MEM1_BLOCK_SIZE //内存表大小

//mem2内存参数设定.mem2的内存池处于外部SRAM里面
#define MEM2_BLOCK_SIZE 32                                    //内存块大小为32字节
#define MEM2_MAX_SIZE 960 * 1024                              //最大管理内存960K
#define MEM2_ALLOC_TABLE_SIZE MEM2_MAX_SIZE / MEM2_BLOCK_SIZE //内存表大小

//内存管理控制器
struct _m_mallco_dev
{
    void (*init)(u8);   //初始化
    u8 (*perused)(u8);     //内存使用率
    u8 *membase[SRAMBANK]; //内存池 管理SRAMBANK个区域的内存
    u16 *memmap[SRAMBANK]; //内存管理状态表
    u8 memrdy[SRAMBANK];   //内存管理是否就绪
};
//extern struct _m_mallco_dev mallco_dev; //在mallco.c里面定义

void customer_memset(void *s, u8 c, u32 count);    //设置内存
void customer_memcpy(void *des, void *src, u32 n); //复制内存
void customer_mem_init(u8 memx);                  //内存管理初始化函数(外/内部调用)
u32 customer_mem_malloc(u8 memx, u32 size);       //内存分配(内部调用)
u8 customer_mem_free(u8 memx, u32 offset);        //内存释放(内部调用)
u8 customer_mem_perused(u8 memx);                 //获得内存使用率(外/内部调用)

////////////////////////////////////////////////////////////////////////////////
//用户调用函数
void customer_free(u8 memx, void *ptr);               //内存释放(外部调用)
void *customer_malloc(u8 memx, u32 size);             //内存分配(外部调用)
void *customer_realloc(u8 memx, void *ptr, u32 size); //重新分配内存(外部调用)
void *customer_calloc(u8 memx, u32 num, u32 size);

#define CmnMemMalloc(size) customer_malloc(SRAMIN, size)
#define CmnMemRealloc(ptr, size) customer_realloc(SRAMIN, ptr, size)
#define CmnMemCalloc(num, size) customer_calloc(SRAMIN, num, size)
#define CmnMemFree(ptr) customer_free(SRAMIN, ptr)
#define CmnMemPerused() customer_mem_perused(SRAMIN)
#endif