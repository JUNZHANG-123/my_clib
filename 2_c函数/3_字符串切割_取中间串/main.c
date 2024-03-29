#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
*left_str和right_str需要比较详细，防止在source_str 中存在子字符串导致定位错误
*right_str 的定位起始点是left_str
*在字符串中取出 left_str  和 right_str 中间的字符串到 dest_str
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

//去除字串
bool cut_sub_str(char *source_str, char *sub_str)
{
	char *p = strstr(source_str, sub_str);
	char tmp_buf[512] = {0};
	
	if (strlen(source_str) > sizeof(tmp_buf) ) {
			printf("err: source_str too long %ld\n", strlen(source_str) );
			return false;
	}
	
	if (p != NULL){
			memcpy(tmp_buf, source_str, p-source_str);
			printf("%s\n", tmp_buf);
			
			if (strlen( &p[strlen(sub_str)] ) != 0) {
				strcat(tmp_buf, &p[strlen(sub_str)]);
			}
			
			memset(source_str, 0, strlen(source_str));
			strcpy(source_str, tmp_buf);
			return true;
	}

	printf("err: no found sub str: %s %s\n", source_str, sub_str );
	return false;
}

int main(int argc, char **argv)
{
#if 0	
	char buf[] = "aabb,1122,2233";
	char out_data[10] = {0};

	cut_str(buf, ",", ",", out_data);

	printf("out_data=%s\n", out_data);//输出 out_data=1122

#else
	char source[50] = "123434,3333,5555,213235,";

	cut_sub_str(source, "3333,");
	printf("%s\n", source);

#endif
	
	return 0;
}


