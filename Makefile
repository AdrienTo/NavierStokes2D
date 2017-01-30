# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sofujikake/Desktop/UPMC/EDP/project/NavierStokes2D

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sofujikake/Desktop/UPMC/EDP/project/NavierStokes2D

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/Applications/CMake.app/Contents/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/Applications/CMake.app/Contents/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/sofujikake/Desktop/UPMC/EDP/project/NavierStokes2D/CMakeFiles /Users/sofujikake/Desktop/UPMC/EDP/project/NavierStokes2D/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/sofujikake/Desktop/UPMC/EDP/project/NavierStokes2D/CMakeFiles 0
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
# Target rules for targets named NavierStokes2D

# Build rule for target.
NavierStokes2D: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 NavierStokes2D
.PHONY : NavierStokes2D

# fast build rule for target.
NavierStokes2D/fast:
	$(MAKE) -f CMakeFiles/NavierStokes2D.dir/build.make CMakeFiles/NavierStokes2D.dir/build
.PHONY : NavierStokes2D/fast

Discretization.o: Discretization.cpp.o

.PHONY : Discretization.o

# target to build an object file
Discretization.cpp.o:
	$(MAKE) -f CMakeFiles/NavierStokes2D.dir/build.make CMakeFiles/NavierStokes2D.dir/Discretization.cpp.o
.PHONY : Discretization.cpp.o

Discretization.i: Discretization.cpp.i

.PHONY : Discretization.i

# target to preprocess a source file
Discretization.cpp.i:
	$(MAKE) -f CMakeFiles/NavierStokes2D.dir/build.make CMakeFiles/NavierStokes2D.dir/Discretization.cpp.i
.PHONY : Discretization.cpp.i

Discretization.s: Discretization.cpp.s

.PHONY : Discretization.s

# target to generate assembly for a file
Discretization.cpp.s:
	$(MAKE) -f CMakeFiles/NavierStokes2D.dir/build.make CMakeFiles/NavierStokes2D.dir/Discretization.cpp.s
.PHONY : Discretization.cpp.s

Mesh1D.o: Mesh1D.cpp.o

.PHONY : Mesh1D.o

# target to build an object file
Mesh1D.cpp.o:
	$(MAKE) -f CMakeFiles/NavierStokes2D.dir/build.make CMakeFiles/NavierStokes2D.dir/Mesh1D.cpp.o
.PHONY : Mesh1D.cpp.o

Mesh1D.i: Mesh1D.cpp.i

.PHONY : Mesh1D.i

# target to preprocess a source file
Mesh1D.cpp.i:
	$(MAKE) -f CMakeFiles/NavierStokes2D.dir/build.make CMakeFiles/NavierStokes2D.dir/Mesh1D.cpp.i
.PHONY : Mesh1D.cpp.i

Mesh1D.s: Mesh1D.cpp.s

.PHONY : Mesh1D.s

# target to generate assembly for a file
Mesh1D.cpp.s:
	$(MAKE) -f CMakeFiles/NavierStokes2D.dir/build.make CMakeFiles/NavierStokes2D.dir/Mesh1D.cpp.s
.PHONY : Mesh1D.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/NavierStokes2D.dir/build.make CMakeFiles/NavierStokes2D.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/NavierStokes2D.dir/build.make CMakeFiles/NavierStokes2D.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/NavierStokes2D.dir/build.make CMakeFiles/NavierStokes2D.dir/main.cpp.s
.PHONY : main.cpp.s

matrix.o: matrix.cpp.o

.PHONY : matrix.o

# target to build an object file
matrix.cpp.o:
	$(MAKE) -f CMakeFiles/NavierStokes2D.dir/build.make CMakeFiles/NavierStokes2D.dir/matrix.cpp.o
.PHONY : matrix.cpp.o

matrix.i: matrix.cpp.i

.PHONY : matrix.i

# target to preprocess a source file
matrix.cpp.i:
	$(MAKE) -f CMakeFiles/NavierStokes2D.dir/build.make CMakeFiles/NavierStokes2D.dir/matrix.cpp.i
.PHONY : matrix.cpp.i

matrix.s: matrix.cpp.s

.PHONY : matrix.s

# target to generate assembly for a file
matrix.cpp.s:
	$(MAKE) -f CMakeFiles/NavierStokes2D.dir/build.make CMakeFiles/NavierStokes2D.dir/matrix.cpp.s
.PHONY : matrix.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... NavierStokes2D"
	@echo "... Discretization.o"
	@echo "... Discretization.i"
	@echo "... Discretization.s"
	@echo "... Mesh1D.o"
	@echo "... Mesh1D.i"
	@echo "... Mesh1D.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... matrix.o"
	@echo "... matrix.i"
	@echo "... matrix.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

