# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/build

# Include any dependencies generated for this target.
include sharedlib/CMakeFiles/jcstest.dir/depend.make

# Include the progress variables for this target.
include sharedlib/CMakeFiles/jcstest.dir/progress.make

# Include the compile flags for this target's objects.
include sharedlib/CMakeFiles/jcstest.dir/flags.make

sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.o: sharedlib/CMakeFiles/jcstest.dir/flags.make
sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.o: ../jcstest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.o"
	cd /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/jcstest.dir/__/jcstest.c.o   -c /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/jcstest.c

sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/jcstest.dir/__/jcstest.c.i"
	cd /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/jcstest.c > CMakeFiles/jcstest.dir/__/jcstest.c.i

sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/jcstest.dir/__/jcstest.c.s"
	cd /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/build/sharedlib && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/jcstest.c -o CMakeFiles/jcstest.dir/__/jcstest.c.s

sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.o.requires:

.PHONY : sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.o.requires

sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.o.provides: sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.o.requires
	$(MAKE) -f sharedlib/CMakeFiles/jcstest.dir/build.make sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.o.provides.build
.PHONY : sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.o.provides

sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.o.provides.build: sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.o


# Object files for target jcstest
jcstest_OBJECTS = \
"CMakeFiles/jcstest.dir/__/jcstest.c.o"

# External object files for target jcstest
jcstest_EXTERNAL_OBJECTS =

jcstest: sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.o
jcstest: sharedlib/CMakeFiles/jcstest.dir/build.make
jcstest: libjpeg.so.62.3.0
jcstest: sharedlib/CMakeFiles/jcstest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../jcstest"
	cd /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/build/sharedlib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jcstest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sharedlib/CMakeFiles/jcstest.dir/build: jcstest

.PHONY : sharedlib/CMakeFiles/jcstest.dir/build

sharedlib/CMakeFiles/jcstest.dir/requires: sharedlib/CMakeFiles/jcstest.dir/__/jcstest.c.o.requires

.PHONY : sharedlib/CMakeFiles/jcstest.dir/requires

sharedlib/CMakeFiles/jcstest.dir/clean:
	cd /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/build/sharedlib && $(CMAKE_COMMAND) -P CMakeFiles/jcstest.dir/cmake_clean.cmake
.PHONY : sharedlib/CMakeFiles/jcstest.dir/clean

sharedlib/CMakeFiles/jcstest.dir/depend:
	cd /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/sharedlib /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/build /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/build/sharedlib /home/yingchen/wrapper_libjpeg/arm_pac/libjpeg-turbo/build/sharedlib/CMakeFiles/jcstest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sharedlib/CMakeFiles/jcstest.dir/depend

