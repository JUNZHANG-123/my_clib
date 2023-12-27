#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include "stb_image_write.h"

#include "img_out.h"

#define LOCAL_IMAGES_FILE		"./imgs.h"
#define LOCAL_OUT_IMAGES_FILE	"./img_out.h"
#define FILE_CACHE_SIZEB		4096

int get_dir_file_num(const char *path)
{
    int count = 0;
    DIR *dp = NULL;
    struct dirent *st;
    struct stat sta;
    int ret = 0;
    char tmp_name[1024]={0};

    if (NULL == (dp = opendir(path))) {
        printf("open dir error!!\n");
        return -1;
    }

    while(1) {
        st = readdir(dp);
        if(NULL == st) { 
            break;
        }
        strcpy(tmp_name, path);
        if(path[strlen(path)-1] != '/')
            strcat(tmp_name,"/");
        strcat(tmp_name,st->d_name);

        if (0 > (ret = stat(tmp_name, &sta))) {
            closedir(dp);
            printf("fs_get_dir_file_num: read stat fail, d_name=%s", st->d_name);
            return -1;
        }
        if(!S_ISDIR(sta.st_mode)) {
            count += 1;
        }   
    }
    closedir(dp);
    return count;
}

uint32_t file_size(const char *fname)
{
    struct stat st;
    stat(fname, &st);
    return st.st_size;
}

void img_change(void)
{
	int file_count = get_dir_file_num("./images");
	char file_path[256] = {0};
	FILE *fp = NULL, *fp2 = NULL;
	uint32_t fsz, nbyte, n;
	uint8_t buff[FILE_CACHE_SIZEB] = {0};
	
	if (NULL == (fp2 = fopen(LOCAL_IMAGES_FILE, "w+")))
	{
		printf("open file failed: %s\r\n", LOCAL_IMAGES_FILE);
		goto EXIT;
	}
	
	fprintf( fp2, "const static unsigned char img_buf[][10*1024] = {");
	
	printf("file_count=%d\n", file_count);
	for (int i = 0; i < file_count; i++)
	{
		snprintf(file_path, sizeof(file_path), "./images/img%05d.jpg", i);
		printf("file_path=%s\n", file_path);
		if (NULL == (fp = fopen(file_path, "r")))
		{
			printf("open file failed: %s\r\n", file_path);
			goto EXIT;
		}
		
		if (0 == (fsz = file_size(file_path)))
		{
			printf("empty file size: %s\r\n", file_path);
		}
		else
		{
			fprintf( fp2, "{");
		}
			
		while (fsz)
		{
			n = (fsz > FILE_CACHE_SIZEB) ? FILE_CACHE_SIZEB : fsz;
			fsz -= n;
			nbyte = fread(buff, 1, n, fp);
			if (nbyte != n)
			{
				printf("read file error: %d, %d\r\n", nbyte, n);
				goto EXIT;
			}

			for (int j = 0; j < nbyte; j++)
			{
				fprintf( fp2, "0x%02x,", buff[j]);
			}
			
			if (fsz == 0)
				fprintf( fp2, "},\r\n");

			printf("write tarball %d bytes\r\n", n);
		}
	}
	fprintf( fp2, "};\r\n");

EXIT:
	if (fp)
		fclose(fp);
	
	if (fp2)
		fclose(fp2);
}

void imgbuf_to_file(void)
{
	system("rm -rf 1.jpg");
	stbi_write_jpg("./1.jpg", 818, 152/2, 1, img_buf,100);

	#if 0
	FILE *fp = NULL;
	uint32_t fsz, nbyte, n;
	
	if (NULL == (fp = fopen("./1.bmp", "wb+")))
	{
		printf("open file failed\r\n");
	}
	else
	{
		int ret = fwrite(img_buf, sizeof(img_buf), 1, fp);
		
		printf("%d %d \r\n", ret, sizeof(img_buf));
		
		fclose(fp);	
	}
	#endif
}

//测试主函数

int main()
{
	img_change();
	imgbuf_to_file();
	return 0;
}
