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
CMAKE_SOURCE_DIR = /home/emma/Downloads/voreen-src-4.3-unix

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/emma/Downloads/voreen-src-4.3-unix

# Utility rule file for voreen_qt_gch.

# Include the progress variables for this target.
include src/qt/CMakeFiles/voreen_qt_gch.dir/progress.make

src/qt/CMakeFiles/voreen_qt_gch: src/qt/pch_qt.h.gch/.c++

src/qt/pch_qt.h.gch/.c++: src/qt/pch_qt.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/Downloads/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating pch_qt.h.gch/.c++"
	cd /home/emma/Downloads/voreen-src-4.3-unix/src/qt && /usr/bin/c++ -fPIC -I/home/emma/Downloads/voreen-src-4.3-unix -I/home/emma/Downloads/voreen-src-4.3-unix/include -I/home/emma/Downloads/voreen-src-4.3-unix/ext -I/home/emma/Downloads/voreen-src-4.3-unix -I/home/emma/Downloads/voreen-src-4.3-unix -I/usr/include -I/usr/include -I/usr/include -I/home/emma/Downloads/voreen-src-4.3-unix/ext/eigen -I/home/emma/Downloads/voreen-src-4.3-unix/modules/connexe/ext/connexe -I/usr/local/include/IL -I/usr/include -I/home/emma/Downloads/voreen-src-4.3-unix/modules/plotting/ext/triangle -I/home/emma/Downloads/voreen-src-4.3-unix/modules/volumelabeling/ext/jama/include -I/usr/include -I/opt/Qt5.1.0/5.1.0/gcc_64/include -I/opt/Qt5.1.0/5.1.0/gcc_64/include/QtWidgets -I/opt/Qt5.1.0/5.1.0/gcc_64/include/QtGui -I/opt/Qt5.1.0/5.1.0/gcc_64/include/QtCore -I/opt/Qt5.1.0/5.1.0/gcc_64/mkspecs/linux-g++ -I/home/emma/Downloads/voreen-src-4.3-unix/src/qt -DVRN_SHARED_LIBS -DUNIX -D__STDC_CONSTANT_MACROS -DTIXML_USE_STL -DTGT_WITHOUT_DEFINES -DEIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS -DVRN_MODULE_ADVANCEDLIGHTING -DVRN_MODULE_BASE -DVRN_MODULE_CONNEXE -DVRN_MODULE_CORE -DVRN_MODULE_DEVIL -DTGT_HAS_DEVIL -DVRN_MODULE_DYNAMICGLSL -DVRN_MODULE_FLOWREEN -DVRN_MODULE_OPENCL -DVRN_MODULE_PLOTTING -DVRN_MODULE_PVM -DVRN_MODULE_RANDOMWALKER -DVRN_MODULE_SEGY -DVRN_MODULE_STAGING -DVRN_MODULE_STEREOSCOPY -DVRN_MODULE_VOLUMELABELING -DVRN_MODULE_ZIP -x c++-header -o /home/emma/Downloads/voreen-src-4.3-unix/src/qt/pch_qt.h.gch/.c++ /home/emma/Downloads/voreen-src-4.3-unix/src/qt/pch_qt.h

voreen_qt_gch: src/qt/CMakeFiles/voreen_qt_gch
voreen_qt_gch: src/qt/pch_qt.h.gch/.c++
voreen_qt_gch: src/qt/CMakeFiles/voreen_qt_gch.dir/build.make
.PHONY : voreen_qt_gch

# Rule to build all files generated by this target.
src/qt/CMakeFiles/voreen_qt_gch.dir/build: voreen_qt_gch
.PHONY : src/qt/CMakeFiles/voreen_qt_gch.dir/build

src/qt/CMakeFiles/voreen_qt_gch.dir/clean:
	cd /home/emma/Downloads/voreen-src-4.3-unix/src/qt && $(CMAKE_COMMAND) -P CMakeFiles/voreen_qt_gch.dir/cmake_clean.cmake
.PHONY : src/qt/CMakeFiles/voreen_qt_gch.dir/clean

src/qt/CMakeFiles/voreen_qt_gch.dir/depend:
	cd /home/emma/Downloads/voreen-src-4.3-unix && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/emma/Downloads/voreen-src-4.3-unix /home/emma/Downloads/voreen-src-4.3-unix/src/qt /home/emma/Downloads/voreen-src-4.3-unix /home/emma/Downloads/voreen-src-4.3-unix/src/qt /home/emma/Downloads/voreen-src-4.3-unix/src/qt/CMakeFiles/voreen_qt_gch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/qt/CMakeFiles/voreen_qt_gch.dir/depend

