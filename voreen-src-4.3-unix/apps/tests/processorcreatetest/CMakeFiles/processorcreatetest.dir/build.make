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
include apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/depend.make

# Include the progress variables for this target.
include apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/progress.make

# Include the compile flags for this target's objects.
include apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/flags.make

apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o: apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/flags.make
apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o: apps/tests/processorcreatetest/processorcreatetest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processorcreatetest && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processorcreatetest/processorcreatetest.cpp

apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.i"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processorcreatetest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processorcreatetest/processorcreatetest.cpp > CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.i

apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.s"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processorcreatetest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processorcreatetest/processorcreatetest.cpp -o CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.s

apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o.requires:
.PHONY : apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o.requires

apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o.provides: apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o.requires
	$(MAKE) -f apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/build.make apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o.provides.build
.PHONY : apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o.provides

apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o.provides.build: apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o

# Object files for target processorcreatetest
processorcreatetest_OBJECTS = \
"CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o"

# External object files for target processorcreatetest
processorcreatetest_EXTERNAL_OBJECTS =

bin/processorcreatetest: apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o
bin/processorcreatetest: apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/build.make
bin/processorcreatetest: bin/libtgt.so
bin/processorcreatetest: bin/libvoreen_core.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libGL.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libSM.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libICE.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libX11.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libXext.so
bin/processorcreatetest: /usr/lib/libGLEW.so
bin/processorcreatetest: /usr/lib/libboost_date_time-mt.so
bin/processorcreatetest: /usr/lib/libboost_prg_exec_monitor-mt.so
bin/processorcreatetest: /usr/lib/libboost_program_options-mt.so
bin/processorcreatetest: /usr/lib/libboost_regex-mt.so
bin/processorcreatetest: /usr/lib/libboost_thread-mt.so
bin/processorcreatetest: /usr/lib/libboost_unit_test_framework-mt.so
bin/processorcreatetest: /usr/lib/libboost_system-mt.so
bin/processorcreatetest: /usr/local/lib/libIL.so
bin/processorcreatetest: /usr/local/lib/libILU.so
bin/processorcreatetest: /usr/lib/libOpenCL.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libz.so
bin/processorcreatetest: bin/libtgt.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libGL.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libSM.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libICE.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libX11.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libXext.so
bin/processorcreatetest: /usr/lib/libGLEW.so
bin/processorcreatetest: /usr/lib/libboost_date_time-mt.so
bin/processorcreatetest: /usr/lib/libboost_prg_exec_monitor-mt.so
bin/processorcreatetest: /usr/lib/libboost_program_options-mt.so
bin/processorcreatetest: /usr/lib/libboost_regex-mt.so
bin/processorcreatetest: /usr/lib/libboost_thread-mt.so
bin/processorcreatetest: /usr/lib/libboost_unit_test_framework-mt.so
bin/processorcreatetest: /usr/lib/libboost_system-mt.so
bin/processorcreatetest: /usr/local/lib/libIL.so
bin/processorcreatetest: /usr/local/lib/libILU.so
bin/processorcreatetest: /usr/lib/libOpenCL.so
bin/processorcreatetest: /usr/lib/x86_64-linux-gnu/libz.so
bin/processorcreatetest: apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/processorcreatetest"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processorcreatetest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/processorcreatetest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/build: bin/processorcreatetest
.PHONY : apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/build

apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/requires: apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/processorcreatetest.cpp.o.requires
.PHONY : apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/requires

apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/clean:
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processorcreatetest && $(CMAKE_COMMAND) -P CMakeFiles/processorcreatetest.dir/cmake_clean.cmake
.PHONY : apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/clean

apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/depend:
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/emma/code/gitrepo/voreen-src-4.3-unix /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processorcreatetest /home/emma/code/gitrepo/voreen-src-4.3-unix /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processorcreatetest /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : apps/tests/processorcreatetest/CMakeFiles/processorcreatetest.dir/depend

