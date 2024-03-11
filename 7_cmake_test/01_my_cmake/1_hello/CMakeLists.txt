cmake_minimum_required(VERSION 3.5) #设置CMake最小版本
project (hello_cmake) #设置工程名
#add_executable(hello_cmake main.c) #生成可执行文件
add_executable(${PROJECT_NAME} main.c) #生成已工程同名二进制文件