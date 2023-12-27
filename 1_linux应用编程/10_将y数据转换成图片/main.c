#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include "img.h"
#include "stb_image_write.h"


//测试主函数

int main()
{

	stbi_write_jpg("./1.jpg", 240, 128, 1, buf, 100);
	return 0;
}
