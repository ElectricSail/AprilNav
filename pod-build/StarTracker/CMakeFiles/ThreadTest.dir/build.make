# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/tristan/Desktop/AprilTags

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tristan/Desktop/AprilTags/pod-build

# Include any dependencies generated for this target.
include StarTracker/CMakeFiles/ThreadTest.dir/depend.make

# Include the progress variables for this target.
include StarTracker/CMakeFiles/ThreadTest.dir/progress.make

# Include the compile flags for this target's objects.
include StarTracker/CMakeFiles/ThreadTest.dir/flags.make

StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o: StarTracker/CMakeFiles/ThreadTest.dir/flags.make
StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o: ../StarTracker/ThreadTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tristan/Desktop/AprilTags/pod-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o"
	cd /home/tristan/Desktop/AprilTags/pod-build/StarTracker && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o -c /home/tristan/Desktop/AprilTags/StarTracker/ThreadTest.cpp

StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ThreadTest.dir/ThreadTest.cpp.i"
	cd /home/tristan/Desktop/AprilTags/pod-build/StarTracker && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tristan/Desktop/AprilTags/StarTracker/ThreadTest.cpp > CMakeFiles/ThreadTest.dir/ThreadTest.cpp.i

StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ThreadTest.dir/ThreadTest.cpp.s"
	cd /home/tristan/Desktop/AprilTags/pod-build/StarTracker && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tristan/Desktop/AprilTags/StarTracker/ThreadTest.cpp -o CMakeFiles/ThreadTest.dir/ThreadTest.cpp.s

StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o.requires:

.PHONY : StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o.requires

StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o.provides: StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o.requires
	$(MAKE) -f StarTracker/CMakeFiles/ThreadTest.dir/build.make StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o.provides.build
.PHONY : StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o.provides

StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o.provides.build: StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o


StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.o: StarTracker/CMakeFiles/ThreadTest.dir/flags.make
StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.o: ../StarTracker/Serial.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tristan/Desktop/AprilTags/pod-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.o"
	cd /home/tristan/Desktop/AprilTags/pod-build/StarTracker && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ThreadTest.dir/Serial.cpp.o -c /home/tristan/Desktop/AprilTags/StarTracker/Serial.cpp

StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ThreadTest.dir/Serial.cpp.i"
	cd /home/tristan/Desktop/AprilTags/pod-build/StarTracker && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tristan/Desktop/AprilTags/StarTracker/Serial.cpp > CMakeFiles/ThreadTest.dir/Serial.cpp.i

StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ThreadTest.dir/Serial.cpp.s"
	cd /home/tristan/Desktop/AprilTags/pod-build/StarTracker && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tristan/Desktop/AprilTags/StarTracker/Serial.cpp -o CMakeFiles/ThreadTest.dir/Serial.cpp.s

StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.o.requires:

.PHONY : StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.o.requires

StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.o.provides: StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.o.requires
	$(MAKE) -f StarTracker/CMakeFiles/ThreadTest.dir/build.make StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.o.provides.build
.PHONY : StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.o.provides

StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.o.provides.build: StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.o


# Object files for target ThreadTest
ThreadTest_OBJECTS = \
"CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o" \
"CMakeFiles/ThreadTest.dir/Serial.cpp.o"

# External object files for target ThreadTest
ThreadTest_EXTERNAL_OBJECTS =

bin/ThreadTest: StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o
bin/ThreadTest: StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.o
bin/ThreadTest: StarTracker/CMakeFiles/ThreadTest.dir/build.make
bin/ThreadTest: lib/libapriltags.a
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.9
bin/ThreadTest: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.9
bin/ThreadTest: StarTracker/CMakeFiles/ThreadTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tristan/Desktop/AprilTags/pod-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../bin/ThreadTest"
	cd /home/tristan/Desktop/AprilTags/pod-build/StarTracker && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ThreadTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
StarTracker/CMakeFiles/ThreadTest.dir/build: bin/ThreadTest

.PHONY : StarTracker/CMakeFiles/ThreadTest.dir/build

StarTracker/CMakeFiles/ThreadTest.dir/requires: StarTracker/CMakeFiles/ThreadTest.dir/ThreadTest.cpp.o.requires
StarTracker/CMakeFiles/ThreadTest.dir/requires: StarTracker/CMakeFiles/ThreadTest.dir/Serial.cpp.o.requires

.PHONY : StarTracker/CMakeFiles/ThreadTest.dir/requires

StarTracker/CMakeFiles/ThreadTest.dir/clean:
	cd /home/tristan/Desktop/AprilTags/pod-build/StarTracker && $(CMAKE_COMMAND) -P CMakeFiles/ThreadTest.dir/cmake_clean.cmake
.PHONY : StarTracker/CMakeFiles/ThreadTest.dir/clean

StarTracker/CMakeFiles/ThreadTest.dir/depend:
	cd /home/tristan/Desktop/AprilTags/pod-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tristan/Desktop/AprilTags /home/tristan/Desktop/AprilTags/StarTracker /home/tristan/Desktop/AprilTags/pod-build /home/tristan/Desktop/AprilTags/pod-build/StarTracker /home/tristan/Desktop/AprilTags/pod-build/StarTracker/CMakeFiles/ThreadTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : StarTracker/CMakeFiles/ThreadTest.dir/depend
