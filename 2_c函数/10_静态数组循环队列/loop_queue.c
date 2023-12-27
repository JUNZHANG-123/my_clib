#include "loop_queue.h"

static int queue[QUEUE_SIZE];
static int head = 0;
static int tail = 0;

//进队列
void lq_en_queue(int value){
    //要先判断队列是否已满
    if ((tail + 1) % QUEUE_SIZE == head) {
        lq_printf("队列已满，无法从队尾插入元素\n");
    }else{

        queue[tail] = value;
        tail = (tail + 1) % QUEUE_SIZE;
    }
}

//出队列
int lq_de_queue(){
    int temp;
    if (tail == head) {
        lq_printf("队列为空，元素无法出队列\n");
    }else{

        temp = queue[head];
        head = (head + 1) % QUEUE_SIZE;
    }

    lq_printf("%d\n",temp);
    return temp;
}

//判断队列是否为空
int lq_is_empty(){
    if (head == tail) {
        lq_printf("队列为空\n");
        return 1;
    }

    lq_printf("队列不为空\n");
    return 0;
}

//判断队列是否已满
/**
 *  我这里判断队满的的方法：
 牺牲一个单元来区分队空和队满，入队时少用一个队列单元。如果数组的大小为Size,那么实际只能存放(Size-1)个元素。（这是比较常用的判满的方式）
 *
 */
int lq_is_full(){
    if ((tail + 1) % QUEUE_SIZE == head) {
        lq_printf("队列已满\n");
        return 1;
    }

    lq_printf("队列未满\n");
    return 0;
}

//打印出队列元素
void lq_print_queue(){
    for (int i = head; i < tail; i++) {
        lq_printf("%d ",queue[i]);
    }
    lq_printf("\n");
}

int lq_queue_init(void *queue, int queue_size)
{
	

}

