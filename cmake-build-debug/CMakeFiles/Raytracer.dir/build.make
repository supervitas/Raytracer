# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nikolaev/Projects/C++/Raytracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nikolaev/Projects/C++/Raytracer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Raytracer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Raytracer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Raytracer.dir/flags.make

CMakeFiles/Raytracer.dir/main.cpp.o: CMakeFiles/Raytracer.dir/flags.make
CMakeFiles/Raytracer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nikolaev/Projects/C++/Raytracer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Raytracer.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Raytracer.dir/main.cpp.o -c /Users/nikolaev/Projects/C++/Raytracer/main.cpp

CMakeFiles/Raytracer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Raytracer.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nikolaev/Projects/C++/Raytracer/main.cpp > CMakeFiles/Raytracer.dir/main.cpp.i

CMakeFiles/Raytracer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Raytracer.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nikolaev/Projects/C++/Raytracer/main.cpp -o CMakeFiles/Raytracer.dir/main.cpp.s

CMakeFiles/Raytracer.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Raytracer.dir/main.cpp.o.requires

CMakeFiles/Raytracer.dir/main.cpp.o.provides: CMakeFiles/Raytracer.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Raytracer.dir/build.make CMakeFiles/Raytracer.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Raytracer.dir/main.cpp.o.provides

CMakeFiles/Raytracer.dir/main.cpp.o.provides.build: CMakeFiles/Raytracer.dir/main.cpp.o


# Object files for target Raytracer
Raytracer_OBJECTS = \
"CMakeFiles/Raytracer.dir/main.cpp.o"

# External object files for target Raytracer
Raytracer_EXTERNAL_OBJECTS =

Raytracer: CMakeFiles/Raytracer.dir/main.cpp.o
Raytracer: CMakeFiles/Raytracer.dir/build.make
Raytracer: CMakeFiles/Raytracer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/nikolaev/Projects/C++/Raytracer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Raytracer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Raytracer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Raytracer.dir/build: Raytracer

.PHONY : CMakeFiles/Raytracer.dir/build

CMakeFiles/Raytracer.dir/requires: CMakeFiles/Raytracer.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Raytracer.dir/requires

CMakeFiles/Raytracer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Raytracer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Raytracer.dir/clean

CMakeFiles/Raytracer.dir/depend:
	cd /Users/nikolaev/Projects/C++/Raytracer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nikolaev/Projects/C++/Raytracer /Users/nikolaev/Projects/C++/Raytracer /Users/nikolaev/Projects/C++/Raytracer/cmake-build-debug /Users/nikolaev/Projects/C++/Raytracer/cmake-build-debug /Users/nikolaev/Projects/C++/Raytracer/cmake-build-debug/CMakeFiles/Raytracer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Raytracer.dir/depend

