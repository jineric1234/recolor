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
CMAKE_SOURCE_DIR = /home/eric/Documents/recolor-tm7-e

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eric/Documents/recolor-tm7-e

# Include any dependencies generated for this target.
include CMakeFiles/test_game_anouamani.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_game_anouamani.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_game_anouamani.dir/flags.make

CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.o: CMakeFiles/test_game_anouamani.dir/flags.make
CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.o: test_game_anouamani.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eric/Documents/recolor-tm7-e/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.o   -c /home/eric/Documents/recolor-tm7-e/test_game_anouamani.c

CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/eric/Documents/recolor-tm7-e/test_game_anouamani.c > CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.i

CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/eric/Documents/recolor-tm7-e/test_game_anouamani.c -o CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.s

# Object files for target test_game_anouamani
test_game_anouamani_OBJECTS = \
"CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.o"

# External object files for target test_game_anouamani
test_game_anouamani_EXTERNAL_OBJECTS =

test_game_anouamani: CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.o
test_game_anouamani: CMakeFiles/test_game_anouamani.dir/build.make
test_game_anouamani: CMakeFiles/test_game_anouamani.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/eric/Documents/recolor-tm7-e/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_game_anouamani"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_game_anouamani.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_game_anouamani.dir/build: test_game_anouamani

.PHONY : CMakeFiles/test_game_anouamani.dir/build

CMakeFiles/test_game_anouamani.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_game_anouamani.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_game_anouamani.dir/clean

CMakeFiles/test_game_anouamani.dir/depend:
	cd /home/eric/Documents/recolor-tm7-e && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eric/Documents/recolor-tm7-e /home/eric/Documents/recolor-tm7-e /home/eric/Documents/recolor-tm7-e /home/eric/Documents/recolor-tm7-e /home/eric/Documents/recolor-tm7-e/CMakeFiles/test_game_anouamani.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_game_anouamani.dir/depend

