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
include tests/libtest/CMakeFiles/lib504.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/libtest/CMakeFiles/lib504.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/libtest/CMakeFiles/lib504.dir/progress.make

# Include the compile flags for this target's objects.
include tests/libtest/CMakeFiles/lib504.dir/flags.make

tests/libtest/CMakeFiles/lib504.dir/lib504.c.o: tests/libtest/CMakeFiles/lib504.dir/flags.make
tests/libtest/CMakeFiles/lib504.dir/lib504.c.o: ../tests/libtest/lib504.c
tests/libtest/CMakeFiles/lib504.dir/lib504.c.o: tests/libtest/CMakeFiles/lib504.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/libtest/CMakeFiles/lib504.dir/lib504.c.o"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/libtest/CMakeFiles/lib504.dir/lib504.c.o -MF CMakeFiles/lib504.dir/lib504.c.o.d -o CMakeFiles/lib504.dir/lib504.c.o -c /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/lib504.c

tests/libtest/CMakeFiles/lib504.dir/lib504.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib504.dir/lib504.c.i"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/lib504.c > CMakeFiles/lib504.dir/lib504.c.i

tests/libtest/CMakeFiles/lib504.dir/lib504.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib504.dir/lib504.c.s"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/lib504.c -o CMakeFiles/lib504.dir/lib504.c.s

tests/libtest/CMakeFiles/lib504.dir/first.c.o: tests/libtest/CMakeFiles/lib504.dir/flags.make
tests/libtest/CMakeFiles/lib504.dir/first.c.o: ../tests/libtest/first.c
tests/libtest/CMakeFiles/lib504.dir/first.c.o: tests/libtest/CMakeFiles/lib504.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/libtest/CMakeFiles/lib504.dir/first.c.o"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/libtest/CMakeFiles/lib504.dir/first.c.o -MF CMakeFiles/lib504.dir/first.c.o.d -o CMakeFiles/lib504.dir/first.c.o -c /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/first.c

tests/libtest/CMakeFiles/lib504.dir/first.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib504.dir/first.c.i"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/first.c > CMakeFiles/lib504.dir/first.c.i

tests/libtest/CMakeFiles/lib504.dir/first.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib504.dir/first.c.s"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/first.c -o CMakeFiles/lib504.dir/first.c.s

tests/libtest/CMakeFiles/lib504.dir/testutil.c.o: tests/libtest/CMakeFiles/lib504.dir/flags.make
tests/libtest/CMakeFiles/lib504.dir/testutil.c.o: ../tests/libtest/testutil.c
tests/libtest/CMakeFiles/lib504.dir/testutil.c.o: tests/libtest/CMakeFiles/lib504.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object tests/libtest/CMakeFiles/lib504.dir/testutil.c.o"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/libtest/CMakeFiles/lib504.dir/testutil.c.o -MF CMakeFiles/lib504.dir/testutil.c.o.d -o CMakeFiles/lib504.dir/testutil.c.o -c /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/testutil.c

tests/libtest/CMakeFiles/lib504.dir/testutil.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib504.dir/testutil.c.i"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/testutil.c > CMakeFiles/lib504.dir/testutil.c.i

tests/libtest/CMakeFiles/lib504.dir/testutil.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib504.dir/testutil.c.s"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest/testutil.c -o CMakeFiles/lib504.dir/testutil.c.s

tests/libtest/CMakeFiles/lib504.dir/__/__/lib/warnless.c.o: tests/libtest/CMakeFiles/lib504.dir/flags.make
tests/libtest/CMakeFiles/lib504.dir/__/__/lib/warnless.c.o: ../lib/warnless.c
tests/libtest/CMakeFiles/lib504.dir/__/__/lib/warnless.c.o: tests/libtest/CMakeFiles/lib504.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object tests/libtest/CMakeFiles/lib504.dir/__/__/lib/warnless.c.o"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/libtest/CMakeFiles/lib504.dir/__/__/lib/warnless.c.o -MF CMakeFiles/lib504.dir/__/__/lib/warnless.c.o.d -o CMakeFiles/lib504.dir/__/__/lib/warnless.c.o -c /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/lib/warnless.c

tests/libtest/CMakeFiles/lib504.dir/__/__/lib/warnless.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib504.dir/__/__/lib/warnless.c.i"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/lib/warnless.c > CMakeFiles/lib504.dir/__/__/lib/warnless.c.i

tests/libtest/CMakeFiles/lib504.dir/__/__/lib/warnless.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib504.dir/__/__/lib/warnless.c.s"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/lib/warnless.c -o CMakeFiles/lib504.dir/__/__/lib/warnless.c.s

# Object files for target lib504
lib504_OBJECTS = \
"CMakeFiles/lib504.dir/lib504.c.o" \
"CMakeFiles/lib504.dir/first.c.o" \
"CMakeFiles/lib504.dir/testutil.c.o" \
"CMakeFiles/lib504.dir/__/__/lib/warnless.c.o"

# External object files for target lib504
lib504_EXTERNAL_OBJECTS =

tests/libtest/lib504: tests/libtest/CMakeFiles/lib504.dir/lib504.c.o
tests/libtest/lib504: tests/libtest/CMakeFiles/lib504.dir/first.c.o
tests/libtest/lib504: tests/libtest/CMakeFiles/lib504.dir/testutil.c.o
tests/libtest/lib504: tests/libtest/CMakeFiles/lib504.dir/__/__/lib/warnless.c.o
tests/libtest/lib504: tests/libtest/CMakeFiles/lib504.dir/build.make
tests/libtest/lib504: lib/libcurl.so
tests/libtest/lib504: /usr/lib/x86_64-linux-gnu/libssl.so
tests/libtest/lib504: /usr/lib/x86_64-linux-gnu/libcrypto.so
tests/libtest/lib504: /usr/lib/x86_64-linux-gnu/libz.so
tests/libtest/lib504: tests/libtest/CMakeFiles/lib504.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable lib504"
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib504.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/libtest/CMakeFiles/lib504.dir/build: tests/libtest/lib504
.PHONY : tests/libtest/CMakeFiles/lib504.dir/build

tests/libtest/CMakeFiles/lib504.dir/clean:
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest && $(CMAKE_COMMAND) -P CMakeFiles/lib504.dir/cmake_clean.cmake
.PHONY : tests/libtest/CMakeFiles/lib504.dir/clean

tests/libtest/CMakeFiles/lib504.dir/depend:
	cd /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1 /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/tests/libtest /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest /mnt/d/ProjectFiles/my_git/my_clib/8_http/1_http_client_post_file/curl-7.54.1/build/tests/libtest/CMakeFiles/lib504.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/libtest/CMakeFiles/lib504.dir/depend

