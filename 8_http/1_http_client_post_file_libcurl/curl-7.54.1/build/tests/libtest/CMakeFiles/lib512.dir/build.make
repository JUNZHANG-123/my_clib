# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build

# Include any dependencies generated for this target.
include tests/libtest/CMakeFiles/lib512.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/libtest/CMakeFiles/lib512.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/libtest/CMakeFiles/lib512.dir/progress.make

# Include the compile flags for this target's objects.
include tests/libtest/CMakeFiles/lib512.dir/flags.make

tests/libtest/CMakeFiles/lib512.dir/lib512.c.o: tests/libtest/CMakeFiles/lib512.dir/flags.make
tests/libtest/CMakeFiles/lib512.dir/lib512.c.o: ../tests/libtest/lib512.c
tests/libtest/CMakeFiles/lib512.dir/lib512.c.o: tests/libtest/CMakeFiles/lib512.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/libtest/CMakeFiles/lib512.dir/lib512.c.o"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/libtest/CMakeFiles/lib512.dir/lib512.c.o -MF CMakeFiles/lib512.dir/lib512.c.o.d -o CMakeFiles/lib512.dir/lib512.c.o -c /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/lib512.c

tests/libtest/CMakeFiles/lib512.dir/lib512.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib512.dir/lib512.c.i"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/lib512.c > CMakeFiles/lib512.dir/lib512.c.i

tests/libtest/CMakeFiles/lib512.dir/lib512.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib512.dir/lib512.c.s"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/lib512.c -o CMakeFiles/lib512.dir/lib512.c.s

tests/libtest/CMakeFiles/lib512.dir/first.c.o: tests/libtest/CMakeFiles/lib512.dir/flags.make
tests/libtest/CMakeFiles/lib512.dir/first.c.o: ../tests/libtest/first.c
tests/libtest/CMakeFiles/lib512.dir/first.c.o: tests/libtest/CMakeFiles/lib512.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/libtest/CMakeFiles/lib512.dir/first.c.o"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/libtest/CMakeFiles/lib512.dir/first.c.o -MF CMakeFiles/lib512.dir/first.c.o.d -o CMakeFiles/lib512.dir/first.c.o -c /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/first.c

tests/libtest/CMakeFiles/lib512.dir/first.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib512.dir/first.c.i"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/first.c > CMakeFiles/lib512.dir/first.c.i

tests/libtest/CMakeFiles/lib512.dir/first.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib512.dir/first.c.s"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/first.c -o CMakeFiles/lib512.dir/first.c.s

# Object files for target lib512
lib512_OBJECTS = \
"CMakeFiles/lib512.dir/lib512.c.o" \
"CMakeFiles/lib512.dir/first.c.o"

# External object files for target lib512
lib512_EXTERNAL_OBJECTS =

tests/libtest/lib512: tests/libtest/CMakeFiles/lib512.dir/lib512.c.o
tests/libtest/lib512: tests/libtest/CMakeFiles/lib512.dir/first.c.o
tests/libtest/lib512: tests/libtest/CMakeFiles/lib512.dir/build.make
tests/libtest/lib512: lib/libcurl.so
tests/libtest/lib512: /usr/lib/x86_64-linux-gnu/libssl.so
tests/libtest/lib512: /usr/lib/x86_64-linux-gnu/libcrypto.so
tests/libtest/lib512: /usr/lib/x86_64-linux-gnu/libz.so
tests/libtest/lib512: tests/libtest/CMakeFiles/lib512.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable lib512"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib512.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/libtest/CMakeFiles/lib512.dir/build: tests/libtest/lib512
.PHONY : tests/libtest/CMakeFiles/lib512.dir/build

tests/libtest/CMakeFiles/lib512.dir/clean:
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && $(CMAKE_COMMAND) -P CMakeFiles/lib512.dir/cmake_clean.cmake
.PHONY : tests/libtest/CMakeFiles/lib512.dir/clean

tests/libtest/CMakeFiles/lib512.dir/depend:
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1 /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest/CMakeFiles/lib512.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/libtest/CMakeFiles/lib512.dir/depend

