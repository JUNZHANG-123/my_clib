#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

bool is_text_utf8(char* str, uint32_t length)
{
	int n_bytes=0;//UFT8可用1-6个字节编码,ASCII用一个字节
	char chr;
	bool is_all_ascii=true; //如果全部都是ASCII, 说明不是UTF-8
	for(int i=0; i<length; ++i)
	{
		chr= *(str+i);
		if( (chr&0x80) != 0 ) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx
			is_all_ascii= false;
		if(n_bytes==0) //如果不是ASCII码,应该是多字节符,计算字节数
		{
			if(chr>=0x80)
			{
				if(chr>=0xFC&&chr<=0xFD)
					n_bytes=6;
				else if(chr>=0xF8)
					n_bytes=5;
				else if(chr>=0xF0)
					n_bytes=4;
				else if(chr>=0xE0)
					n_bytes=3;
				else if(chr>=0xC0)
					n_bytes=2;
				else
					return false;

				n_bytes--;
			}
		}
		else //多字节符的非首字节,应为 10xxxxxx
		{
			if( (chr&0xC0) != 0x80 )
				return false;

			n_bytes--;
		}
	}
	if( n_bytes > 0 ) //违返规则
		return false;
	if( is_all_ascii ) //如果全部都是ASCII, 说明不是UTF-8
		return false;

	return true;
}


int main(void)
{
	char src[] = "你好aaa";
	
	printf("%d\n", is_text_utf8(src, strlen(src)));

	return 0;
}
