# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /home/emma/Downloads/cmake-2.8.11.2-Linux-i386/bin/cmake

# The command to remove a file.
RM = /home/emma/Downloads/cmake-2.8.11.2-Linux-i386/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /home/emma/Downloads/cmake-2.8.11.2-Linux-i386/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/emma/code/gitrepo/voreen-src-4.3-unix

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/emma/code/gitrepo/voreen-src-4.3-unix

# Include any dependencies generated for this target.
include CMakeFiles/octreetest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/octreetest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/octreetest.dir/flags.make

CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o: CMakeFiles/octreetest.dir/flags.make
CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o: modules/staging/octree/test/octreetest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.3-unix/modules/staging/octree/test/octreetest.cpp

CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/emma/code/gitrepo/voreen-src-4.3-unix/modules/staging/octree/test/octreetest.cpp > CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.i

CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/emma/code/gitrepo/voreen-src-4.3-unix/modules/staging/octree/test/octreetest.cpp -o CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.s

CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o.requires:
.PHONY : CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o.requires

CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o.provides: CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o.requires
	$(MAKE) -f CMakeFiles/octreetest.dir/build.make CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o.provides.build
.PHONY : CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o.provides

CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o.provides.build: CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o

# Object files for target octreetest
octreetest_OBJECTS = \
"CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o"

# External object files for target octreetest
octreetest_EXTERNAL_OBJECTS =

bin/octreetest: CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o
bin/octreetest: CMakeFiles/octreetest.dir/build.make
bin/octreetest: bin/libtgt.so
bin/octreetest: bin/libvoreen_core.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libGL.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libSM.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libICE.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libX11.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libXext.so
bin/octreetest: /usr/lib/libGLEW.so
bin/octreetest: /usr/lib/libboost_date_time-mt.so
bin/octreetest: /usr/lib/libboost_prg_exec_monitor-mt.so
bin/octreetest: /usr/lib/libboost_program_options-mt.so
bin/octreetest: /usr/lib/libboost_regex-mt.so
bin/octreetest: /usr/lib/libboost_thread-mt.so
bin/octreetest: /usr/lib/libboost_unit_test_framework-mt.so
bin/octreetest: /usr/lib/libboost_system-mt.so
bin/octreetest: /usr/local/lib/libIL.so
bin/octreetest: /usr/local/lib/libILU.so
bin/octreetest: /usr/lib/libOpenCL.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libz.so
bin/octreetest: bin/libtgt.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libGL.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libSM.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libICE.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libX11.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libXext.so
bin/octreetest: /usr/lib/libGLEW.so
bin/octreetest: /usr/lib/libboost_date_time-mt.so
bin/octreetest: /usr/lib/libboost_prg_exec_monitor-mt.so
bin/octreetest: /usr/lib/libboost_program_options-mt.so
bin/octreetest: /usr/lib/libboost_regex-mt.so
bin/octreetest: /usr/lib/libboost_thread-mt.so
bin/octreetest: /usr/lib/libboost_unit_test_framework-mt.so
bin/octreetest: /usr/lib/libboost_system-mt.so
bin/octreetest: /usr/local/lib/libIL.so
bin/octreetest: /usr/local/lib/libILU.so
bin/octreetest: /usr/lib/libOpenCL.so
bin/octreetest: /usr/lib/x86_64-linux-gnu/libz.so
bin/octreetest: CMakeFiles/octreetest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/octreetest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/octreetest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/octreetest.dir/build: bin/octreetest
.PHONY : CMakeFiles/octreetest.dir/build

CMakeFiles/octreetest.dir/requires: CMakeFiles/octreetest.dir/modules/staging/octree/test/octreetest.cpp.o.requires
.PHONY : CMakeFiles/octreetest.dir/requires

CMakeFiles/octreetest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/octreetest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/octreetest.dir/clean

CMakeFiles/octreetest.dir/depend:
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/emma/code/gitrepo/voreen-src-4.3-unix /home/emma/code/gitrepo/voreen-src-4.3-unix /home/emma/code/gitrepo/voreen-src-4.3-unix /home/emma/code/gitrepo/voreen-src-4.3-unix /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles/octreetest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/octreetest.dir/depend

