#ifndef __FS_COMMON_H__
#define __FS_COMMON_H__
#include <stdint.h>

int fs_get_file_size(const char *file_path);
int fs_get_dir_size(const char *path);
#endif