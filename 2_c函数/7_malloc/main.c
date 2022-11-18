#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "customer_mem.h"
#include "mem_malloc.h"

int main(void)
{

#if 0
	//使用固定模块频繁使用，会产生碎片
	char *p = (char*)CmnMemMalloc(100);
	char *q = (char*)CmnMemMalloc(100);
	printf("p=%p q=%p %d\n", p, q, CmnMemPerused());
	
	CmnMemFree(p);
	p = NULL;
	
	CmnMemFree(q);
	q = NULL;
	
	printf("p=%p q=%p %d\n", p, q, CmnMemPerused());
#else
	int id = 0;
	char *p = NULL;
	
	id = mem_malloc(100);
	if (id == 0) {
		printf("malloc --- fail\n");		
	} else {
		p = mem_buffer(id);

        printf("p = %p, id=%d\n", p, id);		
	}

#endif	
	
	return 0;
}
