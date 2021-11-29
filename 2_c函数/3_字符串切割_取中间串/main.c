#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
*left_str和right_str需要比较详细，防止在source_str 中存在子字符串导致定位错误
*right_str 的定位起始点是left_str
*/
bool cut_str(char *source_str, char *left_str, char *right_str, char *dest_str)
{
	char *p = strstr(source_str, left_str);
	char *pp = NULL;
	
	if (p != NULL){
		//printf("p=%s\n", p);
		pp = strstr(&p[strlen(left_str)], right_str);
		if (pp != NULL){
			//printf("pp=%s\n", pp);
			memcpy(dest_str, &p[strlen(left_str)], pp-p-strlen(left_str));
			return true;
		}
	}

	printf("cut_str false %d %d %d\n", (p == NULL)?0:1, (pp == NULL)?0:1,  (pp < p)?0:1);
	return false;
}


int main(int argc, char **argv)
{
	char buf[] = "aabb,1122,2233";
	char out_data[10] = {0};

	cut_str(buf, ",", ",", out_data);

	printf("out_data=%s\n", out_data);//输出 out_data=1122
	return 0;
}


