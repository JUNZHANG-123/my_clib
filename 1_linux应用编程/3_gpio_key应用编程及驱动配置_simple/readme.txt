基于input子系统的 key 应用编程 和驱动配置

底层驱动使用 wait_event_interruptible 来阻塞，这时候用户空间如果有信号中断都会唤醒 wait_event_interruptible，
这时候驱动通过返回 key_value 值为2 来过滤这类信号；

