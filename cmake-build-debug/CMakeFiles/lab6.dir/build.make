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
CMAKE_SOURCE_DIR = /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab6.dir/flags.make

CMakeFiles/lab6.dir/src/main.cpp.o: CMakeFiles/lab6.dir/flags.make
CMakeFiles/lab6.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab6.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab6.dir/src/main.cpp.o -c /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/src/main.cpp

CMakeFiles/lab6.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab6.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/src/main.cpp > CMakeFiles/lab6.dir/src/main.cpp.i

CMakeFiles/lab6.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab6.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/src/main.cpp -o CMakeFiles/lab6.dir/src/main.cpp.s

CMakeFiles/lab6.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/lab6.dir/src/main.cpp.o.requires

CMakeFiles/lab6.dir/src/main.cpp.o.provides: CMakeFiles/lab6.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab6.dir/build.make CMakeFiles/lab6.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/lab6.dir/src/main.cpp.o.provides

CMakeFiles/lab6.dir/src/main.cpp.o.provides.build: CMakeFiles/lab6.dir/src/main.cpp.o


CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o: CMakeFiles/lab6.dir/flags.make
CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o: ../src/utils/Graphics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o -c /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/src/utils/Graphics.cpp

CMakeFiles/lab6.dir/src/utils/Graphics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab6.dir/src/utils/Graphics.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/src/utils/Graphics.cpp > CMakeFiles/lab6.dir/src/utils/Graphics.cpp.i

CMakeFiles/lab6.dir/src/utils/Graphics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab6.dir/src/utils/Graphics.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/src/utils/Graphics.cpp -o CMakeFiles/lab6.dir/src/utils/Graphics.cpp.s

CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o.requires:

.PHONY : CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o.requires

CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o.provides: CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab6.dir/build.make CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o.provides.build
.PHONY : CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o.provides

CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o.provides.build: CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o


# Object files for target lab6
lab6_OBJECTS = \
"CMakeFiles/lab6.dir/src/main.cpp.o" \
"CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o"

# External object files for target lab6
lab6_EXTERNAL_OBJECTS =

lab6: CMakeFiles/lab6.dir/src/main.cpp.o
lab6: CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o
lab6: CMakeFiles/lab6.dir/build.make
lab6: CMakeFiles/lab6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable lab6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab6.dir/build: lab6

.PHONY : CMakeFiles/lab6.dir/build

CMakeFiles/lab6.dir/requires: CMakeFiles/lab6.dir/src/main.cpp.o.requires
CMakeFiles/lab6.dir/requires: CMakeFiles/lab6.dir/src/utils/Graphics.cpp.o.requires

.PHONY : CMakeFiles/lab6.dir/requires

CMakeFiles/lab6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab6.dir/clean

CMakeFiles/lab6.dir/depend:
	cd /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6 /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6 /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/cmake-build-debug /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/cmake-build-debug /Users/nikitagordia/Documents/Workspace/CLionProjects/lab6/cmake-build-debug/CMakeFiles/lab6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab6.dir/depend

