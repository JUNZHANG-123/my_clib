
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "fs_common.h"

#define gigaByte (1 << 21)
#define megaByte (1 << 11)
#define kiloByte (1 << 1)

int fs_get_file_size(const char *file_path)
{
    int len;
    struct stat fileStat;

    stat(file_path, &fileStat);
    len = fileStat.st_size;

    return len;
}

#if 0
int read_dir_r(char *path) {
    DIR *dp = NULL;
    struct dirent *st;
    struct stat sta;
    int ret = 0;
    char tmp_name[1024]={0};
    dp = opendir(path);
    if(dp == NULL) {
        printf("open dir error!!\n");
        return -1;
    }
    
    while(1) {
        st = readdir(dp);
        if(NULL == st) {    //读取完毕
            break;
        }
        
        strcpy(tmp_name, path);
        if(path[strlen(path)-1] != '/') //判断路径名是否带/
            strcat(tmp_name,"/");
        strcat(tmp_name,st->d_name);  //新文件路径名
        
        ret = stat(tmp_name, &sta); //查看目录下文件属性
        if(ret < 0) {
            printf("read stat fail\n");
            return -1;
        }

        if(S_ISDIR(sta.st_mode)) {  //如果为目录文件
            if( 0 == strcmp("..",st->d_name) || 0 == strcmp(".",st->d_name)) //忽略当前目录和上一层目录
                continue;
            else {
                read_dir_r(tmp_name);  //递归读取
            }
        }
        else { //不为目录则打印文件路径名
            printf("%s\n",tmp_name);
        }
    }
    closedir(dp);
    
    return 0;
}
#endif

//默认返回byte
int fs_get_dir_size(const char *path) 
{	
    DIR *dp = NULL;
    struct dirent *st;
    struct stat sta;
    int ret = 0;
    char tmp_name[1024]={0};
	int size = 0;
	int filecnt = 0;
	int filesum = 0;
	
    dp = opendir(path);
    if(dp == NULL) {
        printf("open dir error!!\n");
        return -1;
    }
    
    while(1) {
        st = readdir(dp);
        if(NULL == st) {    //读取完毕
            break;
        }
        
        strcpy(tmp_name, path);
        if(path[strlen(path)-1] != '/') //判断路径名是否带/
            strcat(tmp_name,"/");
        strcat(tmp_name,st->d_name);  //新文件路径名
        
        ret = stat(tmp_name, &sta); //查看目录下文件属性
        if(ret < 0) {
            printf("read stat fail\n");
            return -1;
        }

        if(S_ISDIR(sta.st_mode)) {  //如果为目录文件
            if( 0 == strcmp("..",st->d_name) || 0 == strcmp(".",st->d_name)) //忽略当前目录和上一层目录
                continue;
            else {
                fs_get_dir_size(tmp_name);  //递归读取
            }
            filecnt += sta.st_size;
        } else { //不为目录则打印文件路径名
            //printf("%s %ldk %ld\n",tmp_name, sta.st_blocks/2, sta.st_size);
            size += sta.st_blocks;
            filesum += sta.st_size;
        }
    }
    closedir(dp);
    //printf("size %d %fG %fM %fK %d\n", (size + 1) / 2, (float)size / gigaByte, (float)size / megaByte, (float)size / kiloByte, size / kiloByte * 1024);
    return size/kiloByte*1024;
}
