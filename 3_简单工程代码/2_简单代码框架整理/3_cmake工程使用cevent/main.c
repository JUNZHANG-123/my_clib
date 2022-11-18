#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cevent.h"

void *test_handler(void *msg, void *msg2)
{
	int *p = (int*)msg;
	int *q = (int*)msg2;
	
	printf( "test_handler:%d %d\n" , *p, *q);
	return NULL;
}

int msg = 1;
int msg2 = 2;

CEVENT_EXPORT(0, test_handler, (void*)&msg, (void*)&msg2);

int main(int argc, char **argv)
{
	ceventInit();
	
	msg = 10;
	msg2 = 3;
	
	printf("---\n");
	ceventPost(0);

	return 0;
}


