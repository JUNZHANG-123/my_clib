#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <assert.h>
#include <string.h>
#include "shmfifo.h"

union semun { int value; };

static void p(int id)
{
	struct sembuf sb[1];
	sb[0].sem_num = 0;					// 信号量编号，如果你的工作不需要使用一组信号量，这个值一般就取为0
	sb[0].sem_op  = -1;					// 信号量值，-1 p操作，+1 v操作
	sb[0].sem_flg = SEM_UNDO;			// SEM_UNDO 当进程退出的时候会还原该进程的信号量操作，可以避免因为进程异常退出而造成的死锁
	semop(id, sb, 1);
}

static void v(int id)
{
	struct sembuf sb[1];
	sb[0].sem_num = 0;
	sb[0].sem_op  = 1;
	sb[0].sem_flg = SEM_UNDO;
	semop(id, sb, 1);
}

shmfifo_t* shmfifo_init(int key, int blocks, int blksz)
{
	shmfifo_t *p = (shmfifo_t*)malloc(sizeof(shmfifo_t));
	assert(p);

	int len = blocks * blksz + sizeof(head_t);
	int shmid = shmget(key, len, 0);
	if ( shmid == -1 ) { // 不存在，创建
		shmid = shmget(key, len, IPC_CREAT|0644);
		if ( shmid == -1 ) perror("shmget"),exit(1);
		p->p_head = (head_t*)shmat(shmid, NULL, 0);
		p->p_head->rd_idx = 0;
		p->p_head->wr_idx = 0;
		p->p_head->blocks = blocks;
		p->p_head->blksz  = blksz;
		p->p_payload = (char*)(p->p_head+1);
		p->shmid = shmid;
		p->sem_empty = semget(key, 1, IPC_CREAT|0644);
		p->sem_full  = semget(key+1, 1, IPC_CREAT|0644);
		p->sem_mutex = semget(key+2, 1, IPC_CREAT|0644);
		union semun su;
		su.value = 0;
		semctl(p->sem_empty, 0, SETVAL, su);
		su.value = blocks;
		semctl(p->sem_full, 0, SETVAL, su);
		su.value = 1;
		semctl(p->sem_mutex, 0, SETVAL, su);
	} else { // 存在
		p->p_head = (head_t*)shmat(shmid, NULL, 0);
		p->p_payload = (char*)(p->p_head+1);
		p->shmid = shmid;
		p->sem_empty = semget(key, 0, 0);
		p->sem_full  = semget(key+1, 0, 0);
		p->sem_mutex = semget(key+2, 0, 0);
	}

	return p;
}

void shmfifo_put(shmfifo_t *fifo, const void *buf)
{
	p(fifo->sem_full);
	p(fifo->sem_mutex);
	memcpy(fifo->p_payload+(fifo->p_head->wr_idx*fifo->p_head->blksz),
			buf, fifo->p_head->blksz);
	fifo->p_head->wr_idx = 
			(fifo->p_head->wr_idx + 1) % fifo->p_head->blocks;
	v(fifo->sem_mutex);
	v(fifo->sem_empty);
}

void shmfifo_get(shmfifo_t *fifo, void *buf)
{
	p(fifo->sem_empty);
	p(fifo->sem_mutex);

	memcpy(buf, fifo->p_payload+(fifo->p_head->rd_idx*fifo->p_head->blksz), fifo->p_head->blksz);
	fifo->p_head->rd_idx = 
			(fifo->p_head->rd_idx+1)%fifo->p_head->blocks;
	
	v(fifo->sem_mutex);
	v(fifo->sem_full);
}

void shmfifo_destroy(shmfifo_t *fifo)
{
	shmdt(fifo->p_head);
	shmctl(fifo->shmid, IPC_RMID, 0);
	semctl(fifo->sem_full, 0, IPC_RMID);
	semctl(fifo->sem_mutex, 0, IPC_RMID);
	semctl(fifo->sem_empty, 0, IPC_RMID);
	free(fifo);
}

