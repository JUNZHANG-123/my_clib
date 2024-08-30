#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int reg_xr872_get_img = 0;
	
	struct timeval t1, t2;
	gettimeofday(&t1, NULL);
	while (!reg_xr872_get_img)
	{
		gettimeofday(&t2, NULL);
		unsigned long diff = (t2.tv_sec-t1.tv_sec) * 1000000 + t2.tv_usec-t1.tv_usec;
		if (diff > 500*1000)
		{
			reg_xr872_get_img = 1;
			printf("timeout\n");
			break;
		}
		usleep(10*1000);
	}
	
	printf("end\n");
	return 0;
}

