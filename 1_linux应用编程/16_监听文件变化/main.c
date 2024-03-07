#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <sys/inotify.h>  
#include <unistd.h>  
 
#define EVENT_NUM 12  
 
char *event_str[EVENT_NUM] =
{
    "IN_ACCESS",
    "IN_MODIFY",
    "IN_ATTRIB",
    "IN_CLOSE_WRITE",
    "IN_CLOSE_NOWRITE",
    "IN_OPEN",
    "IN_MOVED_FROM",
    "IN_MOVED_TO",
    "IN_CREATE",
    "IN_DELETE",
    "IN_DELETE_SELF",
    "IN_MOVE_SELF"
};
 
int main(int argc, char *argv[])
{
    int fd;
    int wd;
    int len;
    int nread;
    char buf[BUFSIZ];
    struct inotify_event *event;
    int i;
 
    if (argc < 2)
    {
        fprintf(stderr, "%s path\n", argv[0]);
        return -1;
    }
 
    fd = inotify_init();
    if (fd < 0)
    {
        fprintf(stderr, "inotify_init failed\n");
        return -1;
    }
 
    wd = inotify_add_watch(fd, argv[1], IN_ALL_EVENTS);
    if (wd < 0)
    {
        fprintf(stderr, "inotify_add_watch %s failed\n", argv[1]);
        return -1;
    }
 
    buf[sizeof(buf) - 1] = 0;
    while ((len = read(fd, buf, sizeof(buf) - 1)) > 0)
    {
        nread = 0;
        while (len > 0)
        {
            event = (struct inotify_event *)&buf[nread];
            for (i = 0; i<EVENT_NUM; i++)
            {
                if ((event->mask >> i) & 1)
                {
                    if (event->len > 0)
                        fprintf(stdout, "%s --- %s\n", event->name, event_str[i]);
                    else
                        fprintf(stdout, "%s --- %s\n", " ", event_str[i]);
                }
            }
            nread = nread + sizeof(struct inotify_event) + event->len;
            len = len - sizeof(struct inotify_event) - event->len;
        }
    }
 
    return 0;
}


#if 0
#include <sys/inotify.h>
 
int inotify_init()//初始化inotify，每个inotify实例对应一个排队的序列
 
int inotify_add_watch(int fd,const char *path,uint32_t mask)//通过文件名和事件掩码添加一个watch对象，返回值是watch对象的描述符
//fd：inotify_init的返回值
//path：要监控的文件路径
//mask：监听文件的哪些事件
/*
    IN_ATTRIB，文件属性被修改
    IN_CLOSE_WRITE，可写文件被关闭
    IN_CLOSE_NOWRITE，不可写文件被关闭
    IN_CREATE，文件/文件夹被创建
    IN_DELETE，文件/文件夹被删除
    IN_DELETE_SELF，被监控的对象本身被删除
    IN_MODIFY，文件被修改
    IN_MOVE_SELF，被监控的对象本身被移动
    IN_MOVED_FROM，文件被移出被监控目录
    IN_MOVED_TO，文件被移入被监控目录
    IN_OPEN，文件被打开
*/
//返回值：表示对那个文件的监视
 
int inotify_rm_watch(int fd,uint32_t wd)//删除监视对象
//fd：inotify_init的返回值
//wd：inotify_add_watch的返回值
 
//文件事件用struct inotify_event表示，通过fd由read函数来读取
//buf是inotify_event结构的数组的指针，BUF_LEN 指定要读取的总长度，buf的长度不能小于BUF_LEN<br>//read读取到的事件数取决于BUF_LEN以及事件中文件名的长度，返回实际读取的长度
size_t len = read (fd, buf, BUF_LEN);
 
struct inotify_event
{
        __s32           wd;             /* watch descriptor */
        __u32           mask;           /* watch mask */
        __u32           cookie;         /* cookie to synchronize two events */
        __u32           len;            /* length (including nulls) of name */
        char            name[0];        /* stub for possible name */
};<br>//文件名是变长的，实际紧跟在该结构的后面，文件名被0填充以保证下一个事件结构能够4字节对齐。<br>//len字段也把name的填充字段统计在内


#endif
