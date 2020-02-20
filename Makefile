# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /autofs/unityaccount/cremi/lalanoix/Pro/recolor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /autofs/unityaccount/cremi/lalanoix/Pro/recolor

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target test
test:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running tests..."
	/usr/bin/ctest --force-new-ctest-process $(ARGS)
.PHONY : test

# Special rule for the target test
test/fast: test

.PHONY : test/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /autofs/unityaccount/cremi/lalanoix/Pro/recolor/CMakeFiles /autofs/unityaccount/cremi/lalanoix/Pro/recolor/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /autofs/unityaccount/cremi/lalanoix/Pro/recolor/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named test_game_anouamani

# Build rule for target.
test_game_anouamani: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_game_anouamani
.PHONY : test_game_anouamani

# fast build rule for target.
test_game_anouamani/fast:
	$(MAKE) -f CMakeFiles/test_game_anouamani.dir/build.make CMakeFiles/test_game_anouamani.dir/build
.PHONY : test_game_anouamani/fast

#=============================================================================
# Target rules for targets named test_game_lalanoix

# Build rule for target.
test_game_lalanoix: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_game_lalanoix
.PHONY : test_game_lalanoix

# fast build rule for target.
test_game_lalanoix/fast:
	$(MAKE) -f CMakeFiles/test_game_lalanoix.dir/build.make CMakeFiles/test_game_lalanoix.dir/build
.PHONY : test_game_lalanoix/fast

#=============================================================================
# Target rules for targets named test_game_zboumedris

# Build rule for target.
test_game_zboumedris: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_game_zboumedris
.PHONY : test_game_zboumedris

# fast build rule for target.
test_game_zboumedris/fast:
	$(MAKE) -f CMakeFiles/test_game_zboumedris.dir/build.make CMakeFiles/test_game_zboumedris.dir/build
.PHONY : test_game_zboumedris/fast

#=============================================================================
# Target rules for targets named test_game_ejin

# Build rule for target.
test_game_ejin: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_game_ejin
.PHONY : test_game_ejin

# fast build rule for target.
test_game_ejin/fast:
	$(MAKE) -f CMakeFiles/test_game_ejin.dir/build.make CMakeFiles/test_game_ejin.dir/build
.PHONY : test_game_ejin/fast

#=============================================================================
# Target rules for targets named ContinuousSubmit

# Build rule for target.
ContinuousSubmit: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ContinuousSubmit
.PHONY : ContinuousSubmit

# fast build rule for target.
ContinuousSubmit/fast:
	$(MAKE) -f CMakeFiles/ContinuousSubmit.dir/build.make CMakeFiles/ContinuousSubmit.dir/build
.PHONY : ContinuousSubmit/fast

#=============================================================================
# Target rules for targets named ContinuousCoverage

# Build rule for target.
ContinuousCoverage: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ContinuousCoverage
.PHONY : ContinuousCoverage

# fast build rule for target.
ContinuousCoverage/fast:
	$(MAKE) -f CMakeFiles/ContinuousCoverage.dir/build.make CMakeFiles/ContinuousCoverage.dir/build
.PHONY : ContinuousCoverage/fast

#=============================================================================
# Target rules for targets named ContinuousTest

# Build rule for target.
ContinuousTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ContinuousTest
.PHONY : ContinuousTest

# fast build rule for target.
ContinuousTest/fast:
	$(MAKE) -f CMakeFiles/ContinuousTest.dir/build.make CMakeFiles/ContinuousTest.dir/build
.PHONY : ContinuousTest/fast

#=============================================================================
# Target rules for targets named ContinuousBuild

# Build rule for target.
ContinuousBuild: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ContinuousBuild
.PHONY : ContinuousBuild

# fast build rule for target.
ContinuousBuild/fast:
	$(MAKE) -f CMakeFiles/ContinuousBuild.dir/build.make CMakeFiles/ContinuousBuild.dir/build
.PHONY : ContinuousBuild/fast

#=============================================================================
# Target rules for targets named ContinuousUpdate

# Build rule for target.
ContinuousUpdate: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ContinuousUpdate
.PHONY : ContinuousUpdate

# fast build rule for target.
ContinuousUpdate/fast:
	$(MAKE) -f CMakeFiles/ContinuousUpdate.dir/build.make CMakeFiles/ContinuousUpdate.dir/build
.PHONY : ContinuousUpdate/fast

#=============================================================================
# Target rules for targets named ContinuousStart

# Build rule for target.
ContinuousStart: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ContinuousStart
.PHONY : ContinuousStart

# fast build rule for target.
ContinuousStart/fast:
	$(MAKE) -f CMakeFiles/ContinuousStart.dir/build.make CMakeFiles/ContinuousStart.dir/build
.PHONY : ContinuousStart/fast

#=============================================================================
# Target rules for targets named NightlyUpdate

# Build rule for target.
NightlyUpdate: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 NightlyUpdate
.PHONY : NightlyUpdate

# fast build rule for target.
NightlyUpdate/fast:
	$(MAKE) -f CMakeFiles/NightlyUpdate.dir/build.make CMakeFiles/NightlyUpdate.dir/build
.PHONY : NightlyUpdate/fast

#=============================================================================
# Target rules for targets named recolor_solve

# Build rule for target.
recolor_solve: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 recolor_solve
.PHONY : recolor_solve

# fast build rule for target.
recolor_solve/fast:
	$(MAKE) -f CMakeFiles/recolor_solve.dir/build.make CMakeFiles/recolor_solve.dir/build
.PHONY : recolor_solve/fast

#=============================================================================
# Target rules for targets named Continuous

# Build rule for target.
Continuous: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Continuous
.PHONY : Continuous

# fast build rule for target.
Continuous/fast:
	$(MAKE) -f CMakeFiles/Continuous.dir/build.make CMakeFiles/Continuous.dir/build
.PHONY : Continuous/fast

#=============================================================================
# Target rules for targets named ContinuousMemCheck

# Build rule for target.
ContinuousMemCheck: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ContinuousMemCheck
.PHONY : ContinuousMemCheck

# fast build rule for target.
ContinuousMemCheck/fast:
	$(MAKE) -f CMakeFiles/ContinuousMemCheck.dir/build.make CMakeFiles/ContinuousMemCheck.dir/build
.PHONY : ContinuousMemCheck/fast

#=============================================================================
# Target rules for targets named Nightly

# Build rule for target.
Nightly: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Nightly
.PHONY : Nightly

# fast build rule for target.
Nightly/fast:
	$(MAKE) -f CMakeFiles/Nightly.dir/build.make CMakeFiles/Nightly.dir/build
.PHONY : Nightly/fast

#=============================================================================
# Target rules for targets named game

# Build rule for target.
game: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 game
.PHONY : game

# fast build rule for target.
game/fast:
	$(MAKE) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/build
.PHONY : game/fast

#=============================================================================
# Target rules for targets named ExperimentalStart

# Build rule for target.
ExperimentalStart: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ExperimentalStart
.PHONY : ExperimentalStart

# fast build rule for target.
ExperimentalStart/fast:
	$(MAKE) -f CMakeFiles/ExperimentalStart.dir/build.make CMakeFiles/ExperimentalStart.dir/build
.PHONY : ExperimentalStart/fast

#=============================================================================
# Target rules for targets named NightlyBuild

# Build rule for target.
NightlyBuild: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 NightlyBuild
.PHONY : NightlyBuild

# fast build rule for target.
NightlyBuild/fast:
	$(MAKE) -f CMakeFiles/NightlyBuild.dir/build.make CMakeFiles/NightlyBuild.dir/build
.PHONY : NightlyBuild/fast

#=============================================================================
# Target rules for targets named NightlyTest

# Build rule for target.
NightlyTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 NightlyTest
.PHONY : NightlyTest

# fast build rule for target.
NightlyTest/fast:
	$(MAKE) -f CMakeFiles/NightlyTest.dir/build.make CMakeFiles/NightlyTest.dir/build
.PHONY : NightlyTest/fast

#=============================================================================
# Target rules for targets named NightlyStart

# Build rule for target.
NightlyStart: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 NightlyStart
.PHONY : NightlyStart

# fast build rule for target.
NightlyStart/fast:
	$(MAKE) -f CMakeFiles/NightlyStart.dir/build.make CMakeFiles/NightlyStart.dir/build
.PHONY : NightlyStart/fast

#=============================================================================
# Target rules for targets named NightlyMemoryCheck

# Build rule for target.
NightlyMemoryCheck: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 NightlyMemoryCheck
.PHONY : NightlyMemoryCheck

# fast build rule for target.
NightlyMemoryCheck/fast:
	$(MAKE) -f CMakeFiles/NightlyMemoryCheck.dir/build.make CMakeFiles/NightlyMemoryCheck.dir/build
.PHONY : NightlyMemoryCheck/fast

#=============================================================================
# Target rules for targets named NightlyMemCheck

# Build rule for target.
NightlyMemCheck: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 NightlyMemCheck
.PHONY : NightlyMemCheck

# fast build rule for target.
NightlyMemCheck/fast:
	$(MAKE) -f CMakeFiles/NightlyMemCheck.dir/build.make CMakeFiles/NightlyMemCheck.dir/build
.PHONY : NightlyMemCheck/fast

#=============================================================================
# Target rules for targets named ExperimentalSubmit

# Build rule for target.
ExperimentalSubmit: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ExperimentalSubmit
.PHONY : ExperimentalSubmit

# fast build rule for target.
ExperimentalSubmit/fast:
	$(MAKE) -f CMakeFiles/ExperimentalSubmit.dir/build.make CMakeFiles/ExperimentalSubmit.dir/build
.PHONY : ExperimentalSubmit/fast

#=============================================================================
# Target rules for targets named Experimental

# Build rule for target.
Experimental: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Experimental
.PHONY : Experimental

# fast build rule for target.
Experimental/fast:
	$(MAKE) -f CMakeFiles/Experimental.dir/build.make CMakeFiles/Experimental.dir/build
.PHONY : Experimental/fast

#=============================================================================
# Target rules for targets named NightlySubmit

# Build rule for target.
NightlySubmit: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 NightlySubmit
.PHONY : NightlySubmit

# fast build rule for target.
NightlySubmit/fast:
	$(MAKE) -f CMakeFiles/NightlySubmit.dir/build.make CMakeFiles/NightlySubmit.dir/build
.PHONY : NightlySubmit/fast

#=============================================================================
# Target rules for targets named ContinuousConfigure

# Build rule for target.
ContinuousConfigure: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ContinuousConfigure
.PHONY : ContinuousConfigure

# fast build rule for target.
ContinuousConfigure/fast:
	$(MAKE) -f CMakeFiles/ContinuousConfigure.dir/build.make CMakeFiles/ContinuousConfigure.dir/build
.PHONY : ContinuousConfigure/fast

#=============================================================================
# Target rules for targets named NightlyCoverage

# Build rule for target.
NightlyCoverage: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 NightlyCoverage
.PHONY : NightlyCoverage

# fast build rule for target.
NightlyCoverage/fast:
	$(MAKE) -f CMakeFiles/NightlyCoverage.dir/build.make CMakeFiles/NightlyCoverage.dir/build
.PHONY : NightlyCoverage/fast

#=============================================================================
# Target rules for targets named ExperimentalUpdate

# Build rule for target.
ExperimentalUpdate: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ExperimentalUpdate
.PHONY : ExperimentalUpdate

# fast build rule for target.
ExperimentalUpdate/fast:
	$(MAKE) -f CMakeFiles/ExperimentalUpdate.dir/build.make CMakeFiles/ExperimentalUpdate.dir/build
.PHONY : ExperimentalUpdate/fast

#=============================================================================
# Target rules for targets named ExperimentalConfigure

# Build rule for target.
ExperimentalConfigure: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ExperimentalConfigure
.PHONY : ExperimentalConfigure

# fast build rule for target.
ExperimentalConfigure/fast:
	$(MAKE) -f CMakeFiles/ExperimentalConfigure.dir/build.make CMakeFiles/ExperimentalConfigure.dir/build
.PHONY : ExperimentalConfigure/fast

#=============================================================================
# Target rules for targets named ExperimentalCoverage

# Build rule for target.
ExperimentalCoverage: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ExperimentalCoverage
.PHONY : ExperimentalCoverage

# fast build rule for target.
ExperimentalCoverage/fast:
	$(MAKE) -f CMakeFiles/ExperimentalCoverage.dir/build.make CMakeFiles/ExperimentalCoverage.dir/build
.PHONY : ExperimentalCoverage/fast

#=============================================================================
# Target rules for targets named ExperimentalBuild

# Build rule for target.
ExperimentalBuild: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ExperimentalBuild
.PHONY : ExperimentalBuild

# fast build rule for target.
ExperimentalBuild/fast:
	$(MAKE) -f CMakeFiles/ExperimentalBuild.dir/build.make CMakeFiles/ExperimentalBuild.dir/build
.PHONY : ExperimentalBuild/fast

#=============================================================================
# Target rules for targets named NightlyConfigure

# Build rule for target.
NightlyConfigure: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 NightlyConfigure
.PHONY : NightlyConfigure

# fast build rule for target.
NightlyConfigure/fast:
	$(MAKE) -f CMakeFiles/NightlyConfigure.dir/build.make CMakeFiles/NightlyConfigure.dir/build
.PHONY : NightlyConfigure/fast

#=============================================================================
# Target rules for targets named ExperimentalTest

# Build rule for target.
ExperimentalTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ExperimentalTest
.PHONY : ExperimentalTest

# fast build rule for target.
ExperimentalTest/fast:
	$(MAKE) -f CMakeFiles/ExperimentalTest.dir/build.make CMakeFiles/ExperimentalTest.dir/build
.PHONY : ExperimentalTest/fast

#=============================================================================
# Target rules for targets named recolor_text

# Build rule for target.
recolor_text: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 recolor_text
.PHONY : recolor_text

# fast build rule for target.
recolor_text/fast:
	$(MAKE) -f CMakeFiles/recolor_text.dir/build.make CMakeFiles/recolor_text.dir/build
.PHONY : recolor_text/fast

#=============================================================================
# Target rules for targets named ExperimentalMemCheck

# Build rule for target.
ExperimentalMemCheck: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ExperimentalMemCheck
.PHONY : ExperimentalMemCheck

# fast build rule for target.
ExperimentalMemCheck/fast:
	$(MAKE) -f CMakeFiles/ExperimentalMemCheck.dir/build.make CMakeFiles/ExperimentalMemCheck.dir/build
.PHONY : ExperimentalMemCheck/fast

game.o: game.c.o

.PHONY : game.o

# target to build an object file
game.c.o:
	$(MAKE) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game.c.o
.PHONY : game.c.o

game.i: game.c.i

.PHONY : game.i

# target to preprocess a source file
game.c.i:
	$(MAKE) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game.c.i
.PHONY : game.c.i

game.s: game.c.s

.PHONY : game.s

# target to generate assembly for a file
game.c.s:
	$(MAKE) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game.c.s
.PHONY : game.c.s

game_io.o: game_io.c.o

.PHONY : game_io.o

# target to build an object file
game_io.c.o:
	$(MAKE) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game_io.c.o
.PHONY : game_io.c.o

game_io.i: game_io.c.i

.PHONY : game_io.i

# target to preprocess a source file
game_io.c.i:
	$(MAKE) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game_io.c.i
.PHONY : game_io.c.i

game_io.s: game_io.c.s

.PHONY : game_io.s

# target to generate assembly for a file
game_io.c.s:
	$(MAKE) -f CMakeFiles/game.dir/build.make CMakeFiles/game.dir/game_io.c.s
.PHONY : game_io.c.s

recolor_solve.o: recolor_solve.c.o

.PHONY : recolor_solve.o

# target to build an object file
recolor_solve.c.o:
	$(MAKE) -f CMakeFiles/recolor_solve.dir/build.make CMakeFiles/recolor_solve.dir/recolor_solve.c.o
.PHONY : recolor_solve.c.o

recolor_solve.i: recolor_solve.c.i

.PHONY : recolor_solve.i

# target to preprocess a source file
recolor_solve.c.i:
	$(MAKE) -f CMakeFiles/recolor_solve.dir/build.make CMakeFiles/recolor_solve.dir/recolor_solve.c.i
.PHONY : recolor_solve.c.i

recolor_solve.s: recolor_solve.c.s

.PHONY : recolor_solve.s

# target to generate assembly for a file
recolor_solve.c.s:
	$(MAKE) -f CMakeFiles/recolor_solve.dir/build.make CMakeFiles/recolor_solve.dir/recolor_solve.c.s
.PHONY : recolor_solve.c.s

recolor_text.o: recolor_text.c.o

.PHONY : recolor_text.o

# target to build an object file
recolor_text.c.o:
	$(MAKE) -f CMakeFiles/recolor_text.dir/build.make CMakeFiles/recolor_text.dir/recolor_text.c.o
.PHONY : recolor_text.c.o

recolor_text.i: recolor_text.c.i

.PHONY : recolor_text.i

# target to preprocess a source file
recolor_text.c.i:
	$(MAKE) -f CMakeFiles/recolor_text.dir/build.make CMakeFiles/recolor_text.dir/recolor_text.c.i
.PHONY : recolor_text.c.i

recolor_text.s: recolor_text.c.s

.PHONY : recolor_text.s

# target to generate assembly for a file
recolor_text.c.s:
	$(MAKE) -f CMakeFiles/recolor_text.dir/build.make CMakeFiles/recolor_text.dir/recolor_text.c.s
.PHONY : recolor_text.c.s

test_game_anouamani.o: test_game_anouamani.c.o

.PHONY : test_game_anouamani.o

# target to build an object file
test_game_anouamani.c.o:
	$(MAKE) -f CMakeFiles/test_game_anouamani.dir/build.make CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.o
.PHONY : test_game_anouamani.c.o

test_game_anouamani.i: test_game_anouamani.c.i

.PHONY : test_game_anouamani.i

# target to preprocess a source file
test_game_anouamani.c.i:
	$(MAKE) -f CMakeFiles/test_game_anouamani.dir/build.make CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.i
.PHONY : test_game_anouamani.c.i

test_game_anouamani.s: test_game_anouamani.c.s

.PHONY : test_game_anouamani.s

# target to generate assembly for a file
test_game_anouamani.c.s:
	$(MAKE) -f CMakeFiles/test_game_anouamani.dir/build.make CMakeFiles/test_game_anouamani.dir/test_game_anouamani.c.s
.PHONY : test_game_anouamani.c.s

test_game_ejin.o: test_game_ejin.c.o

.PHONY : test_game_ejin.o

# target to build an object file
test_game_ejin.c.o:
	$(MAKE) -f CMakeFiles/test_game_ejin.dir/build.make CMakeFiles/test_game_ejin.dir/test_game_ejin.c.o
.PHONY : test_game_ejin.c.o

test_game_ejin.i: test_game_ejin.c.i

.PHONY : test_game_ejin.i

# target to preprocess a source file
test_game_ejin.c.i:
	$(MAKE) -f CMakeFiles/test_game_ejin.dir/build.make CMakeFiles/test_game_ejin.dir/test_game_ejin.c.i
.PHONY : test_game_ejin.c.i

test_game_ejin.s: test_game_ejin.c.s

.PHONY : test_game_ejin.s

# target to generate assembly for a file
test_game_ejin.c.s:
	$(MAKE) -f CMakeFiles/test_game_ejin.dir/build.make CMakeFiles/test_game_ejin.dir/test_game_ejin.c.s
.PHONY : test_game_ejin.c.s

test_game_lalanoix.o: test_game_lalanoix.c.o

.PHONY : test_game_lalanoix.o

# target to build an object file
test_game_lalanoix.c.o:
	$(MAKE) -f CMakeFiles/test_game_lalanoix.dir/build.make CMakeFiles/test_game_lalanoix.dir/test_game_lalanoix.c.o
.PHONY : test_game_lalanoix.c.o

test_game_lalanoix.i: test_game_lalanoix.c.i

.PHONY : test_game_lalanoix.i

# target to preprocess a source file
test_game_lalanoix.c.i:
	$(MAKE) -f CMakeFiles/test_game_lalanoix.dir/build.make CMakeFiles/test_game_lalanoix.dir/test_game_lalanoix.c.i
.PHONY : test_game_lalanoix.c.i

test_game_lalanoix.s: test_game_lalanoix.c.s

.PHONY : test_game_lalanoix.s

# target to generate assembly for a file
test_game_lalanoix.c.s:
	$(MAKE) -f CMakeFiles/test_game_lalanoix.dir/build.make CMakeFiles/test_game_lalanoix.dir/test_game_lalanoix.c.s
.PHONY : test_game_lalanoix.c.s

test_game_zboumedris.o: test_game_zboumedris.c.o

.PHONY : test_game_zboumedris.o

# target to build an object file
test_game_zboumedris.c.o:
	$(MAKE) -f CMakeFiles/test_game_zboumedris.dir/build.make CMakeFiles/test_game_zboumedris.dir/test_game_zboumedris.c.o
.PHONY : test_game_zboumedris.c.o

test_game_zboumedris.i: test_game_zboumedris.c.i

.PHONY : test_game_zboumedris.i

# target to preprocess a source file
test_game_zboumedris.c.i:
	$(MAKE) -f CMakeFiles/test_game_zboumedris.dir/build.make CMakeFiles/test_game_zboumedris.dir/test_game_zboumedris.c.i
.PHONY : test_game_zboumedris.c.i

test_game_zboumedris.s: test_game_zboumedris.c.s

.PHONY : test_game_zboumedris.s

# target to generate assembly for a file
test_game_zboumedris.c.s:
	$(MAKE) -f CMakeFiles/test_game_zboumedris.dir/build.make CMakeFiles/test_game_zboumedris.dir/test_game_zboumedris.c.s
.PHONY : test_game_zboumedris.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... test_game_anouamani"
	@echo "... test_game_lalanoix"
	@echo "... test_game_zboumedris"
	@echo "... test_game_ejin"
	@echo "... ContinuousSubmit"
	@echo "... ContinuousCoverage"
	@echo "... ContinuousTest"
	@echo "... ContinuousBuild"
	@echo "... ContinuousUpdate"
	@echo "... ContinuousStart"
	@echo "... NightlyUpdate"
	@echo "... recolor_solve"
	@echo "... Continuous"
	@echo "... ContinuousMemCheck"
	@echo "... Nightly"
	@echo "... edit_cache"
	@echo "... game"
	@echo "... ExperimentalStart"
	@echo "... NightlyBuild"
	@echo "... NightlyTest"
	@echo "... NightlyStart"
	@echo "... NightlyMemoryCheck"
	@echo "... NightlyMemCheck"
	@echo "... ExperimentalSubmit"
	@echo "... Experimental"
	@echo "... NightlySubmit"
	@echo "... ContinuousConfigure"
	@echo "... NightlyCoverage"
	@echo "... ExperimentalUpdate"
	@echo "... test"
	@echo "... ExperimentalConfigure"
	@echo "... ExperimentalCoverage"
	@echo "... ExperimentalBuild"
	@echo "... NightlyConfigure"
	@echo "... ExperimentalTest"
	@echo "... recolor_text"
	@echo "... ExperimentalMemCheck"
	@echo "... game.o"
	@echo "... game.i"
	@echo "... game.s"
	@echo "... game_io.o"
	@echo "... game_io.i"
	@echo "... game_io.s"
	@echo "... recolor_solve.o"
	@echo "... recolor_solve.i"
	@echo "... recolor_solve.s"
	@echo "... recolor_text.o"
	@echo "... recolor_text.i"
	@echo "... recolor_text.s"
	@echo "... test_game_anouamani.o"
	@echo "... test_game_anouamani.i"
	@echo "... test_game_anouamani.s"
	@echo "... test_game_ejin.o"
	@echo "... test_game_ejin.i"
	@echo "... test_game_ejin.s"
	@echo "... test_game_lalanoix.o"
	@echo "... test_game_lalanoix.i"
	@echo "... test_game_lalanoix.s"
	@echo "... test_game_zboumedris.o"
	@echo "... test_game_zboumedris.i"
	@echo "... test_game_zboumedris.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

