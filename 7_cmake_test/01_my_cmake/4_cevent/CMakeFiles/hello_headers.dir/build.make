# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /workspace/my_cmake/4_cevent

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /workspace/my_cmake/4_cevent

# Include any dependencies generated for this target.
include CMakeFiles/hello_headers.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hello_headers.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hello_headers.dir/flags.make

CMakeFiles/hello_headers.dir/cevent.c.o: CMakeFiles/hello_headers.dir/flags.make
CMakeFiles/hello_headers.dir/cevent.c.o: cevent.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspace/my_cmake/4_cevent/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/hello_headers.dir/cevent.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello_headers.dir/cevent.c.o   -c /workspace/my_cmake/4_cevent/cevent.c

CMakeFiles/hello_headers.dir/cevent.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_headers.dir/cevent.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspace/my_cmake/4_cevent/cevent.c > CMakeFiles/hello_headers.dir/cevent.c.i

CMakeFiles/hello_headers.dir/cevent.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_headers.dir/cevent.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspace/my_cmake/4_cevent/cevent.c -o CMakeFiles/hello_headers.dir/cevent.c.s

CMakeFiles/hello_headers.dir/main.c.o: CMakeFiles/hello_headers.dir/flags.make
CMakeFiles/hello_headers.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/workspace/my_cmake/4_cevent/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/hello_headers.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/hello_headers.dir/main.c.o   -c /workspace/my_cmake/4_cevent/main.c

CMakeFiles/hello_headers.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_headers.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /workspace/my_cmake/4_cevent/main.c > CMakeFiles/hello_headers.dir/main.c.i

CMakeFiles/hello_headers.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_headers.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /workspace/my_cmake/4_cevent/main.c -o CMakeFiles/hello_headers.dir/main.c.s

# Object files for target hello_headers
hello_headers_OBJECTS = \
"CMakeFiles/hello_headers.dir/cevent.c.o" \
"CMakeFiles/hello_headers.dir/main.c.o"

# External object files for target hello_headers
hello_headers_EXTERNAL_OBJECTS =

hello_headers: CMakeFiles/hello_headers.dir/cevent.c.o
hello_headers: CMakeFiles/hello_headers.dir/main.c.o
hello_headers: CMakeFiles/hello_headers.dir/build.make
hello_headers: CMakeFiles/hello_headers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/workspace/my_cmake/4_cevent/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable hello_headers"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hello_headers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hello_headers.dir/build: hello_headers

.PHONY : CMakeFiles/hello_headers.dir/build

CMakeFiles/hello_headers.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hello_headers.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hello_headers.dir/clean

CMakeFiles/hello_headers.dir/depend:
	cd /workspace/my_cmake/4_cevent && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /workspace/my_cmake/4_cevent /workspace/my_cmake/4_cevent /workspace/my_cmake/4_cevent /workspace/my_cmake/4_cevent /workspace/my_cmake/4_cevent/CMakeFiles/hello_headers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hello_headers.dir/depend

