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
	//char buf[] = "0";				//没有匹配到字符也不会报错，返回未知值
	//char buf[] = "0,123";
	//char buf[] = "0, 123";		// 空格自动忽略
	char buf[] = "0, 123:123";		// :123非转化类型跳过
	int a, b;
	
	sscanf(buf, "%d,%d", &a, &b);
	
	printf("%d %d\n", a, b);
	return 0;
}
