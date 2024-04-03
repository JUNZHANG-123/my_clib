#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	int a = 3;
	int b = a?:1;		// 判断a 是否为true，是则用a 值即不赋值
		
	printf("b=%d\n", b);
	return 0;
}
