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
CMAKE_SOURCE_DIR = /mnt/d/ProjectFiles/httpserver.h/test/functional

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/ProjectFiles/httpserver.h/test/functional/build

# Include any dependencies generated for this target.
include CMakeFiles/functional-test-server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/functional-test-server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/functional-test-server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/functional-test-server.dir/flags.make

CMakeFiles/functional-test-server.dir/main.o: CMakeFiles/functional-test-server.dir/flags.make
CMakeFiles/functional-test-server.dir/main.o: ../main.c
CMakeFiles/functional-test-server.dir/main.o: CMakeFiles/functional-test-server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/ProjectFiles/httpserver.h/test/functional/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/functional-test-server.dir/main.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/functional-test-server.dir/main.o -MF CMakeFiles/functional-test-server.dir/main.o.d -o CMakeFiles/functional-test-server.dir/main.o -c /mnt/d/ProjectFiles/httpserver.h/test/functional/main.c

CMakeFiles/functional-test-server.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/functional-test-server.dir/main.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/d/ProjectFiles/httpserver.h/test/functional/main.c > CMakeFiles/functional-test-server.dir/main.i

CMakeFiles/functional-test-server.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/functional-test-server.dir/main.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/d/ProjectFiles/httpserver.h/test/functional/main.c -o CMakeFiles/functional-test-server.dir/main.s

# Object files for target functional-test-server
functional__test__server_OBJECTS = \
"CMakeFiles/functional-test-server.dir/main.o"

# External object files for target functional-test-server
functional__test__server_EXTERNAL_OBJECTS =

functional-test-server: CMakeFiles/functional-test-server.dir/main.o
functional-test-server: CMakeFiles/functional-test-server.dir/build.make
functional-test-server: CMakeFiles/functional-test-server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/ProjectFiles/httpserver.h/test/functional/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable functional-test-server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/functional-test-server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/functional-test-server.dir/build: functional-test-server
.PHONY : CMakeFiles/functional-test-server.dir/build

CMakeFiles/functional-test-server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/functional-test-server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/functional-test-server.dir/clean

CMakeFiles/functional-test-server.dir/depend:
	cd /mnt/d/ProjectFiles/httpserver.h/test/functional/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/ProjectFiles/httpserver.h/test/functional /mnt/d/ProjectFiles/httpserver.h/test/functional /mnt/d/ProjectFiles/httpserver.h/test/functional/build /mnt/d/ProjectFiles/httpserver.h/test/functional/build /mnt/d/ProjectFiles/httpserver.h/test/functional/build/CMakeFiles/functional-test-server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/functional-test-server.dir/depend

