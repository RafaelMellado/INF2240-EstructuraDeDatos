# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rafaelmellado/CLionProjects/Supermercado

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rafaelmellado/CLionProjects/Supermercado/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Supermercado.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Supermercado.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Supermercado.dir/flags.make

CMakeFiles/Supermercado.dir/main.c.o: CMakeFiles/Supermercado.dir/flags.make
CMakeFiles/Supermercado.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rafaelmellado/CLionProjects/Supermercado/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Supermercado.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Supermercado.dir/main.c.o -c /Users/rafaelmellado/CLionProjects/Supermercado/main.c

CMakeFiles/Supermercado.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Supermercado.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/rafaelmellado/CLionProjects/Supermercado/main.c > CMakeFiles/Supermercado.dir/main.c.i

CMakeFiles/Supermercado.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Supermercado.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/rafaelmellado/CLionProjects/Supermercado/main.c -o CMakeFiles/Supermercado.dir/main.c.s

# Object files for target Supermercado
Supermercado_OBJECTS = \
"CMakeFiles/Supermercado.dir/main.c.o"

# External object files for target Supermercado
Supermercado_EXTERNAL_OBJECTS =

Supermercado: CMakeFiles/Supermercado.dir/main.c.o
Supermercado: CMakeFiles/Supermercado.dir/build.make
Supermercado: CMakeFiles/Supermercado.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/rafaelmellado/CLionProjects/Supermercado/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Supermercado"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Supermercado.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Supermercado.dir/build: Supermercado
.PHONY : CMakeFiles/Supermercado.dir/build

CMakeFiles/Supermercado.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Supermercado.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Supermercado.dir/clean

CMakeFiles/Supermercado.dir/depend:
	cd /Users/rafaelmellado/CLionProjects/Supermercado/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rafaelmellado/CLionProjects/Supermercado /Users/rafaelmellado/CLionProjects/Supermercado /Users/rafaelmellado/CLionProjects/Supermercado/cmake-build-debug /Users/rafaelmellado/CLionProjects/Supermercado/cmake-build-debug /Users/rafaelmellado/CLionProjects/Supermercado/cmake-build-debug/CMakeFiles/Supermercado.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Supermercado.dir/depend
