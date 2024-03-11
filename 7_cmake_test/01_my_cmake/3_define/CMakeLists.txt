cmake_minimum_required(VERSION 3.5)
project (hello_cmake)

# 要同时开启Wall和Werror
# 显示所有警告
# 警告变成错误
# 定义宏 TYPE_B
#add_definitions("-Wall -Werror -DTEST_DEBUG")
add_definitions("-Wall -Werror")

option(TEST_DEBUG "option for debug" OFF)
if (TEST_DEBUG) 
	add_definitions(-DTEST_DEBUG)
endif(TEST_DEBUG)

add_executable(${PROJECT_NAME} main.c)
