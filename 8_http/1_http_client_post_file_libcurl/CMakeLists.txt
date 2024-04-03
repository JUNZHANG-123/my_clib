CMAKE_MINIMUM_REQUIRED( VERSION 2.8)
 
PROJECT(mytest)

include_directories(".")
 
add_executable(${PROJECT_NAME} main.c)
message(${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/libcurl.so")