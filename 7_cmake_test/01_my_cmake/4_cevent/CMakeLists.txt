cmake_minimum_required(VERSION 3.5)

project (cevent_cmake)

file(GLOB SOURCES "src/*.c" "*.c")
message("SOURCES=${SOURCES}")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(cevent_cmake
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/script.lds")
target_link_options(${PROJECT_NAME} PUBLIC -T script.lds)