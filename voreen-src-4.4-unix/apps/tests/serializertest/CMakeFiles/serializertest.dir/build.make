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
CMAKE_SOURCE_DIR = /home/emma/code/gitrepo/voreen-src-4.4-unix

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/emma/code/gitrepo/voreen-src-4.4-unix

# Include any dependencies generated for this target.
include apps/tests/serializertest/CMakeFiles/serializertest.dir/depend.make

# Include the progress variables for this target.
include apps/tests/serializertest/CMakeFiles/serializertest.dir/progress.make

# Include the compile flags for this target's objects.
include apps/tests/serializertest/CMakeFiles/serializertest.dir/flags.make

apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.o: apps/tests/serializertest/CMakeFiles/serializertest.dir/flags.make
apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.o: apps/tests/serializertest/serializertest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.4-unix/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.o"
	cd /home/emma/code/gitrepo/voreen-src-4.4-unix/apps/tests/serializertest && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/serializertest.dir/serializertest.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.4-unix/apps/tests/serializertest/serializertest.cpp

apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serializertest.dir/serializertest.cpp.i"
	cd /home/emma/code/gitrepo/voreen-src-4.4-unix/apps/tests/serializertest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/emma/code/gitrepo/voreen-src-4.4-unix/apps/tests/serializertest/serializertest.cpp > CMakeFiles/serializertest.dir/serializertest.cpp.i

apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serializertest.dir/serializertest.cpp.s"
	cd /home/emma/code/gitrepo/voreen-src-4.4-unix/apps/tests/serializertest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/emma/code/gitrepo/voreen-src-4.4-unix/apps/tests/serializertest/serializertest.cpp -o CMakeFiles/serializertest.dir/serializertest.cpp.s

apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.o.requires:
.PHONY : apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.o.requires

apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.o.provides: apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.o.requires
	$(MAKE) -f apps/tests/serializertest/CMakeFiles/serializertest.dir/build.make apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.o.provides.build
.PHONY : apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.o.provides

apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.o.provides.build: apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.o

# Object files for target serializertest
serializertest_OBJECTS = \
"CMakeFiles/serializertest.dir/serializertest.cpp.o"

# External object files for target serializertest
serializertest_EXTERNAL_OBJECTS =

bin/serializertest: apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.o
bin/serializertest: apps/tests/serializertest/CMakeFiles/serializertest.dir/build.make
bin/serializertest: bin/libtgt.so
bin/serializertest: bin/libvoreen_core.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libGL.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libSM.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libICE.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libX11.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libXext.so
bin/serializertest: /usr/lib/libGLEW.so
bin/serializertest: /usr/lib/libboost_date_time-mt.so
bin/serializertest: /usr/lib/libboost_prg_exec_monitor-mt.so
bin/serializertest: /usr/lib/libboost_program_options-mt.so
bin/serializertest: /usr/lib/libboost_regex-mt.so
bin/serializertest: /usr/lib/libboost_thread-mt.so
bin/serializertest: /usr/lib/libboost_unit_test_framework-mt.so
bin/serializertest: /usr/lib/libboost_system-mt.so
bin/serializertest: /usr/local/lib/libIL.so
bin/serializertest: /usr/local/lib/libILU.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libz.so
bin/serializertest: bin/libtgt.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libGL.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libSM.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libICE.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libX11.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libXext.so
bin/serializertest: /usr/lib/libGLEW.so
bin/serializertest: /usr/lib/libboost_date_time-mt.so
bin/serializertest: /usr/lib/libboost_prg_exec_monitor-mt.so
bin/serializertest: /usr/lib/libboost_program_options-mt.so
bin/serializertest: /usr/lib/libboost_regex-mt.so
bin/serializertest: /usr/lib/libboost_thread-mt.so
bin/serializertest: /usr/lib/libboost_unit_test_framework-mt.so
bin/serializertest: /usr/lib/libboost_system-mt.so
bin/serializertest: /usr/local/lib/libIL.so
bin/serializertest: /usr/local/lib/libILU.so
bin/serializertest: /usr/lib/x86_64-linux-gnu/libz.so
bin/serializertest: apps/tests/serializertest/CMakeFiles/serializertest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../bin/serializertest"
	cd /home/emma/code/gitrepo/voreen-src-4.4-unix/apps/tests/serializertest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serializertest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
apps/tests/serializertest/CMakeFiles/serializertest.dir/build: bin/serializertest
.PHONY : apps/tests/serializertest/CMakeFiles/serializertest.dir/build

apps/tests/serializertest/CMakeFiles/serializertest.dir/requires: apps/tests/serializertest/CMakeFiles/serializertest.dir/serializertest.cpp.o.requires
.PHONY : apps/tests/serializertest/CMakeFiles/serializertest.dir/requires

apps/tests/serializertest/CMakeFiles/serializertest.dir/clean:
	cd /home/emma/code/gitrepo/voreen-src-4.4-unix/apps/tests/serializertest && $(CMAKE_COMMAND) -P CMakeFiles/serializertest.dir/cmake_clean.cmake
.PHONY : apps/tests/serializertest/CMakeFiles/serializertest.dir/clean

apps/tests/serializertest/CMakeFiles/serializertest.dir/depend:
	cd /home/emma/code/gitrepo/voreen-src-4.4-unix && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/emma/code/gitrepo/voreen-src-4.4-unix /home/emma/code/gitrepo/voreen-src-4.4-unix/apps/tests/serializertest /home/emma/code/gitrepo/voreen-src-4.4-unix /home/emma/code/gitrepo/voreen-src-4.4-unix/apps/tests/serializertest /home/emma/code/gitrepo/voreen-src-4.4-unix/apps/tests/serializertest/CMakeFiles/serializertest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : apps/tests/serializertest/CMakeFiles/serializertest.dir/depend

