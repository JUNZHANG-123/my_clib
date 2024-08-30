#ifndef __BL_TIMER_H__
#define __BL_TIMER_H__
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>

#define BL_FOREVER_REPEAT       (0xffffffff)

typedef void* (*timeout_cb)(void *);

typedef struct timer_handle {
	int             timer_id;
    uint32_t        repeat_count;
    uint32_t        timeout;    
	timeout_cb      cb;
} bl_timer_handle_t;

/**
 * @brief    bl_timer 全局初始化接口
 *
 * @return : 0 成功；非0 失败
 */
int bl_timer_init(void);

/**
 * @brief    开启定时器
 *
 * @param *timer_id : 定时器id
 * @param repeat_count : 重复次数，BL_FOREVER_REPEAT 表示一直循环
 * @param timeout_ms : 超时时间，最小10ms
 * @param cb : 超时回调
 * @return : 0 成功；非0 失败
 */
int bl_timer_start(int *timer_id, uint32_t repeat_count, uint32_t timeout_ms, timeout_cb cb);

/**
 * @brief    开启一次性定时器
 *
 * @param *timer_id : 定时器id
 * @param timeout_ms : 超时时间，最小10ms
 * @param cb : 超时回调
 * @return : 0 成功；非0 失败
 */
int bl_timer_start_once(int *timer_id, uint32_t timeout_ms, timeout_cb cb);

/**
 * @brief    判断定时器是否存在
 *
 * @param timer_id : 定时器id
 * @return : 0 成功；非0 失败
 */
int bl_timer_stop(int *timer_id);

/**
 * @brief    修改定时器时间
 *
 * @param timer_id : 定时器id
 * @param timeout_ms : 超时时间，最小10ms
 * @param repeat_count : 重复次数
 * @return : 0 成功；非0 失败
 */
int bl_timer_change(int timer_id, uint32_t timeout_ms, uint32_t repeat_count);

/**
 * @brief    判断定时器是否存在
 *
 * @param timer_id : 定时器id
 * @return : 0 成功；非0 失败
 */
int bl_timer_is_exit(int timer_id);
#endif