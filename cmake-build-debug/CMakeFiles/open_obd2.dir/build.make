# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/me/dev/open-obd2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/me/dev/open-obd2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/open_obd2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/open_obd2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/open_obd2.dir/flags.make

CMakeFiles/open_obd2.dir/src/main.cpp.o: CMakeFiles/open_obd2.dir/flags.make
CMakeFiles/open_obd2.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/dev/open-obd2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/open_obd2.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/open_obd2.dir/src/main.cpp.o -c /home/me/dev/open-obd2/src/main.cpp

CMakeFiles/open_obd2.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/open_obd2.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/dev/open-obd2/src/main.cpp > CMakeFiles/open_obd2.dir/src/main.cpp.i

CMakeFiles/open_obd2.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/open_obd2.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/dev/open-obd2/src/main.cpp -o CMakeFiles/open_obd2.dir/src/main.cpp.s

CMakeFiles/open_obd2.dir/src/Config.cpp.o: CMakeFiles/open_obd2.dir/flags.make
CMakeFiles/open_obd2.dir/src/Config.cpp.o: ../src/Config.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/dev/open-obd2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/open_obd2.dir/src/Config.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/open_obd2.dir/src/Config.cpp.o -c /home/me/dev/open-obd2/src/Config.cpp

CMakeFiles/open_obd2.dir/src/Config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/open_obd2.dir/src/Config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/dev/open-obd2/src/Config.cpp > CMakeFiles/open_obd2.dir/src/Config.cpp.i

CMakeFiles/open_obd2.dir/src/Config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/open_obd2.dir/src/Config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/dev/open-obd2/src/Config.cpp -o CMakeFiles/open_obd2.dir/src/Config.cpp.s

CMakeFiles/open_obd2.dir/lib/easylogging++.cc.o: CMakeFiles/open_obd2.dir/flags.make
CMakeFiles/open_obd2.dir/lib/easylogging++.cc.o: ../lib/easylogging++.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/dev/open-obd2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/open_obd2.dir/lib/easylogging++.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/open_obd2.dir/lib/easylogging++.cc.o -c /home/me/dev/open-obd2/lib/easylogging++.cc

CMakeFiles/open_obd2.dir/lib/easylogging++.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/open_obd2.dir/lib/easylogging++.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/dev/open-obd2/lib/easylogging++.cc > CMakeFiles/open_obd2.dir/lib/easylogging++.cc.i

CMakeFiles/open_obd2.dir/lib/easylogging++.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/open_obd2.dir/lib/easylogging++.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/dev/open-obd2/lib/easylogging++.cc -o CMakeFiles/open_obd2.dir/lib/easylogging++.cc.s

# Object files for target open_obd2
open_obd2_OBJECTS = \
"CMakeFiles/open_obd2.dir/src/main.cpp.o" \
"CMakeFiles/open_obd2.dir/src/Config.cpp.o" \
"CMakeFiles/open_obd2.dir/lib/easylogging++.cc.o"

# External object files for target open_obd2
open_obd2_EXTERNAL_OBJECTS =

open_obd2: CMakeFiles/open_obd2.dir/src/main.cpp.o
open_obd2: CMakeFiles/open_obd2.dir/src/Config.cpp.o
open_obd2: CMakeFiles/open_obd2.dir/lib/easylogging++.cc.o
open_obd2: CMakeFiles/open_obd2.dir/build.make
open_obd2: CMakeFiles/open_obd2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/me/dev/open-obd2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable open_obd2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/open_obd2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/open_obd2.dir/build: open_obd2

.PHONY : CMakeFiles/open_obd2.dir/build

CMakeFiles/open_obd2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/open_obd2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/open_obd2.dir/clean

CMakeFiles/open_obd2.dir/depend:
	cd /home/me/dev/open-obd2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/me/dev/open-obd2 /home/me/dev/open-obd2 /home/me/dev/open-obd2/cmake-build-debug /home/me/dev/open-obd2/cmake-build-debug /home/me/dev/open-obd2/cmake-build-debug/CMakeFiles/open_obd2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/open_obd2.dir/depend

