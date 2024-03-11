#include <stdio.h>


int main(int argc, char **argv)
{
	#ifdef TEST_DEBUG
	printf("hello cmake define TEST_DEBUG\n");
	#else
	printf("hello cmake no define TEST_DEBUG\n");
	#endif
	return 0;
}