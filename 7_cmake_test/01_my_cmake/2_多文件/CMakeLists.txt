cmake_minimum_required(VERSION 3.5)

project (hello_headers)

file(GLOB SOURCES "src/*.c" "*.c")
message("SOURCES=${SOURCES}")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(hello_headers
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src
)
