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
include apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/depend.make

# Include the progress variables for this target.
include apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/progress.make

# Include the compile flags for this target's objects.
include apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/flags.make

apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o: apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/flags.make
apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o: apps/tests/processornetworktest/processornetworktest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processornetworktest && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processornetworktest/processornetworktest.cpp

apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/processornetworktest.dir/processornetworktest.cpp.i"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processornetworktest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processornetworktest/processornetworktest.cpp > CMakeFiles/processornetworktest.dir/processornetworktest.cpp.i

apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/processornetworktest.dir/processornetworktest.cpp.s"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processornetworktest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processornetworktest/processornetworktest.cpp -o CMakeFiles/processornetworktest.dir/processornetworktest.cpp.s

apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o.requires:
.PHONY : apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o.requires

apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o.provides: apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o.requires
	$(MAKE) -f apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/build.make apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o.provides.build
.PHONY : apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o.provides

apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o.provides.build: apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o

# Object files for target processornetworktest
processornetworktest_OBJECTS = \
"CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o"

# External object files for target processornetworktest
processornetworktest_EXTERNAL_OBJECTS =

bin/processornetworktest: apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o
bin/processornetworktest: apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/build.make
bin/processornetworktest: bin/libtgt.so
bin/processornetworktest: bin/libvoreen_core.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libGL.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libSM.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libICE.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libX11.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libXext.so
bin/processornetworktest: /usr/lib/libGLEW.so
bin/processornetworktest: /usr/lib/libboost_date_time-mt.so
bin/processornetworktest: /usr/lib/libboost_prg_exec_monitor-mt.so
bin/processornetworktest: /usr/lib/libboost_program_options-mt.so
bin/processornetworktest: /usr/lib/libboost_regex-mt.so
bin/processornetworktest: /usr/lib/libboost_thread-mt.so
bin/processornetworktest: /usr/lib/libboost_unit_test_framework-mt.so
bin/processornetworktest: /usr/lib/libboost_system-mt.so
bin/processornetworktest: /usr/local/lib/libIL.so
bin/processornetworktest: /usr/local/lib/libILU.so
bin/processornetworktest: /usr/lib/libOpenCL.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libz.so
bin/processornetworktest: bin/libtgt.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libGL.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libSM.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libICE.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libX11.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libXext.so
bin/processornetworktest: /usr/lib/libGLEW.so
bin/processornetworktest: /usr/lib/libboost_date_time-mt.so
bin/processornetworktest: /usr/lib/libboost_prg_exec_monitor-mt.so
bin/processornetworktest: /usr/lib/libboost_program_options-mt.so
bin/processornetworktest: /usr/lib/libboost_regex-mt.so
bin/processornetworktest: /usr/lib/libboost_thread-mt.so
bin/processornetworktest: /usr/lib/libboost_unit_test_framework-mt.so
bin/processornetworktest: /usr/lib/libboost_system-mt.so
bin/processornetworktest: /usr/local/lib/libIL.so
bin/processornetworktest: /usr/local/lib/libILU.so
bin/processornetworktest: /usr/lib/libOpenCL.so
bin/processornetworktest: /usr/lib/x86_64-linux-gnu/libz.so
bin/processornetworktest: apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/processornetworktest"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processornetworktest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/processornetworktest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/build: bin/processornetworktest
.PHONY : apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/build

apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/requires: apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/processornetworktest.cpp.o.requires
.PHONY : apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/requires

apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/clean:
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processornetworktest && $(CMAKE_COMMAND) -P CMakeFiles/processornetworktest.dir/cmake_clean.cmake
.PHONY : apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/clean

apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/depend:
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/emma/code/gitrepo/voreen-src-4.3-unix /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processornetworktest /home/emma/code/gitrepo/voreen-src-4.3-unix /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processornetworktest /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : apps/tests/processornetworktest/CMakeFiles/processornetworktest.dir/depend
