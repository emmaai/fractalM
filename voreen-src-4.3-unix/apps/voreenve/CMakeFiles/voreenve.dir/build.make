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
include apps/voreenve/CMakeFiles/voreenve.dir/depend.make

# Include the progress variables for this target.
include apps/voreenve/CMakeFiles/voreenve.dir/progress.make

# Include the compile flags for this target's objects.
include apps/voreenve/CMakeFiles/voreenve.dir/flags.make

apps/voreenve/moc_voreenmainwindow.cpp: apps/voreenve/voreenmainwindow.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_voreenmainwindow.cpp"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /opt/Qt5.1.0/5.1.0/gcc_64/bin/moc -o /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/moc_voreenmainwindow.cpp /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenmainwindow.h

apps/voreenve/moc_voreenveapplication.cpp: apps/voreenve/voreenveapplication.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_voreenveapplication.cpp"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /opt/Qt5.1.0/5.1.0/gcc_64/bin/moc -o /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/moc_voreenveapplication.cpp /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenveapplication.h

apps/voreenve/moc_voreenvisualization.cpp: apps/voreenve/voreenvisualization.h
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_voreenvisualization.cpp"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /opt/Qt5.1.0/5.1.0/gcc_64/bin/moc -o /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/moc_voreenvisualization.cpp /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenvisualization.h

apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/icons/clear_dependency.png
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/icons/development-mode.png
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/icons/visualization-mode.png
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/image/aboutbox.png
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/image/splash.png
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/widgetstyle/closebutton.png
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/widgetstyle/highlight-dockwidget.png
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/widgetstyle/highlight-menu.png
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/widgetstyle/maximizebutton.png
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/widgetstyle/menu.png
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/widgetstyle/scrollbar.png
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/widgetstyle/toolbarhandle.png
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/widgetstyle/undockbutton.png
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/widgetstyle/voreen.qss
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/voreenve.qrc.depends
apps/voreenve/qrc_voreenve.cpp: apps/voreenve/resource/voreenve.qrc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating qrc_voreenve.cpp"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /opt/Qt5.1.0/5.1.0/gcc_64/bin/rcc -name voreenve -o /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/qrc_voreenve.cpp /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/resource/voreenve.qrc

apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.o: apps/voreenve/CMakeFiles/voreenve.dir/flags.make
apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.o: apps/voreenve/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.o"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -o CMakeFiles/voreenve.dir/main.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/main.cpp

apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voreenve.dir/main.cpp.i"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -E /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/main.cpp > CMakeFiles/voreenve.dir/main.cpp.i

apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voreenve.dir/main.cpp.s"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -S /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/main.cpp -o CMakeFiles/voreenve.dir/main.cpp.s

apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.o.requires:
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.o.requires

apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.o.provides: apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.o.requires
	$(MAKE) -f apps/voreenve/CMakeFiles/voreenve.dir/build.make apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.o.provides.build
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.o.provides

apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.o.provides.build: apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.o

apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o: apps/voreenve/CMakeFiles/voreenve.dir/flags.make
apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o: apps/voreenve/voreenmainwindow.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -o CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenmainwindow.cpp

apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voreenve.dir/voreenmainwindow.cpp.i"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -E /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenmainwindow.cpp > CMakeFiles/voreenve.dir/voreenmainwindow.cpp.i

apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voreenve.dir/voreenmainwindow.cpp.s"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -S /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenmainwindow.cpp -o CMakeFiles/voreenve.dir/voreenmainwindow.cpp.s

apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o.requires:
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o.requires

apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o.provides: apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o.requires
	$(MAKE) -f apps/voreenve/CMakeFiles/voreenve.dir/build.make apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o.provides.build
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o.provides

apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o.provides.build: apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o

apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o: apps/voreenve/CMakeFiles/voreenve.dir/flags.make
apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o: apps/voreenve/voreenmoduleve.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -o CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenmoduleve.cpp

apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voreenve.dir/voreenmoduleve.cpp.i"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -E /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenmoduleve.cpp > CMakeFiles/voreenve.dir/voreenmoduleve.cpp.i

apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voreenve.dir/voreenmoduleve.cpp.s"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -S /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenmoduleve.cpp -o CMakeFiles/voreenve.dir/voreenmoduleve.cpp.s

apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o.requires:
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o.requires

apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o.provides: apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o.requires
	$(MAKE) -f apps/voreenve/CMakeFiles/voreenve.dir/build.make apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o.provides.build
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o.provides

apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o.provides.build: apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o

apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.o: apps/voreenve/CMakeFiles/voreenve.dir/flags.make
apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.o: apps/voreenve/voreenveapplication.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.o"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -o CMakeFiles/voreenve.dir/voreenveapplication.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenveapplication.cpp

apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voreenve.dir/voreenveapplication.cpp.i"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -E /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenveapplication.cpp > CMakeFiles/voreenve.dir/voreenveapplication.cpp.i

apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voreenve.dir/voreenveapplication.cpp.s"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -S /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenveapplication.cpp -o CMakeFiles/voreenve.dir/voreenveapplication.cpp.s

apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.o.requires:
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.o.requires

apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.o.provides: apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.o.requires
	$(MAKE) -f apps/voreenve/CMakeFiles/voreenve.dir/build.make apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.o.provides.build
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.o.provides

apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.o.provides.build: apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.o

apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.o: apps/voreenve/CMakeFiles/voreenve.dir/flags.make
apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.o: apps/voreenve/voreenveplugin.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.o"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -o CMakeFiles/voreenve.dir/voreenveplugin.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenveplugin.cpp

apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voreenve.dir/voreenveplugin.cpp.i"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -E /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenveplugin.cpp > CMakeFiles/voreenve.dir/voreenveplugin.cpp.i

apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voreenve.dir/voreenveplugin.cpp.s"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -S /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenveplugin.cpp -o CMakeFiles/voreenve.dir/voreenveplugin.cpp.s

apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.o.requires:
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.o.requires

apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.o.provides: apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.o.requires
	$(MAKE) -f apps/voreenve/CMakeFiles/voreenve.dir/build.make apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.o.provides.build
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.o.provides

apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.o.provides.build: apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.o

apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.o: apps/voreenve/CMakeFiles/voreenve.dir/flags.make
apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.o: apps/voreenve/voreenvisualization.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.o"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -o CMakeFiles/voreenve.dir/voreenvisualization.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenvisualization.cpp

apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voreenve.dir/voreenvisualization.cpp.i"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -E /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenvisualization.cpp > CMakeFiles/voreenve.dir/voreenvisualization.cpp.i

apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voreenve.dir/voreenvisualization.cpp.s"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -S /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/voreenvisualization.cpp -o CMakeFiles/voreenve.dir/voreenvisualization.cpp.s

apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.o.requires:
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.o.requires

apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.o.provides: apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.o.requires
	$(MAKE) -f apps/voreenve/CMakeFiles/voreenve.dir/build.make apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.o.provides.build
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.o.provides

apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.o.provides.build: apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.o

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o: apps/voreenve/CMakeFiles/voreenve.dir/flags.make
apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o: apps/voreenve/moc_voreenmainwindow.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -o CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/moc_voreenmainwindow.cpp

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.i"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -E /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/moc_voreenmainwindow.cpp > CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.i

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.s"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -S /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/moc_voreenmainwindow.cpp -o CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.s

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o.requires:
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o.requires

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o.provides: apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o.requires
	$(MAKE) -f apps/voreenve/CMakeFiles/voreenve.dir/build.make apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o.provides.build
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o.provides

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o.provides.build: apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o: apps/voreenve/CMakeFiles/voreenve.dir/flags.make
apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o: apps/voreenve/moc_voreenveapplication.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -o CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/moc_voreenveapplication.cpp

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.i"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -E /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/moc_voreenveapplication.cpp > CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.i

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.s"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -S /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/moc_voreenveapplication.cpp -o CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.s

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o.requires:
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o.requires

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o.provides: apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o.requires
	$(MAKE) -f apps/voreenve/CMakeFiles/voreenve.dir/build.make apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o.provides.build
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o.provides

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o.provides.build: apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o: apps/voreenve/CMakeFiles/voreenve.dir/flags.make
apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o: apps/voreenve/moc_voreenvisualization.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -o CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/moc_voreenvisualization.cpp

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.i"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -E /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/moc_voreenvisualization.cpp > CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.i

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.s"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -S /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/moc_voreenvisualization.cpp -o CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.s

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o.requires:
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o.requires

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o.provides: apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o.requires
	$(MAKE) -f apps/voreenve/CMakeFiles/voreenve.dir/build.make apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o.provides.build
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o.provides

apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o.provides.build: apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o

apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o: apps/voreenve/CMakeFiles/voreenve.dir/flags.make
apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o: apps/voreenve/qrc_voreenve.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/emma/code/gitrepo/voreen-src-4.3-unix/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -o CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o -c /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/qrc_voreenve.cpp

apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voreenve.dir/qrc_voreenve.cpp.i"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -E /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/qrc_voreenve.cpp > CMakeFiles/voreenve.dir/qrc_voreenve.cpp.i

apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voreenve.dir/qrc_voreenve.cpp.s"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -include pch_ve.h -Winvalid-pch -S /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/qrc_voreenve.cpp -o CMakeFiles/voreenve.dir/qrc_voreenve.cpp.s

apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o.requires:
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o.requires

apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o.provides: apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o.requires
	$(MAKE) -f apps/voreenve/CMakeFiles/voreenve.dir/build.make apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o.provides.build
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o.provides

apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o.provides.build: apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o

# Object files for target voreenve
voreenve_OBJECTS = \
"CMakeFiles/voreenve.dir/main.cpp.o" \
"CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o" \
"CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o" \
"CMakeFiles/voreenve.dir/voreenveapplication.cpp.o" \
"CMakeFiles/voreenve.dir/voreenveplugin.cpp.o" \
"CMakeFiles/voreenve.dir/voreenvisualization.cpp.o" \
"CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o" \
"CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o" \
"CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o" \
"CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o"

# External object files for target voreenve
voreenve_EXTERNAL_OBJECTS =

bin/voreenve: apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.o
bin/voreenve: apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o
bin/voreenve: apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o
bin/voreenve: apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.o
bin/voreenve: apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.o
bin/voreenve: apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.o
bin/voreenve: apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o
bin/voreenve: apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o
bin/voreenve: apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o
bin/voreenve: apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o
bin/voreenve: apps/voreenve/CMakeFiles/voreenve.dir/build.make
bin/voreenve: bin/libtgt.so
bin/voreenve: bin/libvoreen_core.so
bin/voreenve: bin/libvoreen_qt.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libGL.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libSM.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libICE.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libX11.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libXext.so
bin/voreenve: /usr/lib/libGLEW.so
bin/voreenve: /usr/lib/libboost_date_time-mt.so
bin/voreenve: /usr/lib/libboost_prg_exec_monitor-mt.so
bin/voreenve: /usr/lib/libboost_program_options-mt.so
bin/voreenve: /usr/lib/libboost_regex-mt.so
bin/voreenve: /usr/lib/libboost_thread-mt.so
bin/voreenve: /usr/lib/libboost_unit_test_framework-mt.so
bin/voreenve: /usr/lib/libboost_system-mt.so
bin/voreenve: /usr/local/lib/libIL.so
bin/voreenve: /usr/local/lib/libILU.so
bin/voreenve: /usr/lib/libOpenCL.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libz.so
bin/voreenve: /opt/Qt5.1.0/5.1.0/gcc_64/lib/libQt5Widgets.so.5.1.0
bin/voreenve: /opt/Qt5.1.0/5.1.0/gcc_64/lib/libQt5Core.so.5.1.0
bin/voreenve: /opt/Qt5.1.0/5.1.0/gcc_64/lib/libQt5OpenGL.so.5.1.0
bin/voreenve: /opt/Qt5.1.0/5.1.0/gcc_64/lib/libQt5Gui.so.5.1.0
bin/voreenve: bin/libvoreen_core.so
bin/voreenve: bin/libtgt.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libGL.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libSM.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libICE.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libX11.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libXext.so
bin/voreenve: /usr/lib/libGLEW.so
bin/voreenve: /usr/lib/libboost_date_time-mt.so
bin/voreenve: /usr/lib/libboost_prg_exec_monitor-mt.so
bin/voreenve: /usr/lib/libboost_program_options-mt.so
bin/voreenve: /usr/lib/libboost_regex-mt.so
bin/voreenve: /usr/lib/libboost_thread-mt.so
bin/voreenve: /usr/lib/libboost_unit_test_framework-mt.so
bin/voreenve: /usr/lib/libboost_system-mt.so
bin/voreenve: /usr/local/lib/libIL.so
bin/voreenve: /usr/local/lib/libILU.so
bin/voreenve: /usr/lib/libOpenCL.so
bin/voreenve: /usr/lib/x86_64-linux-gnu/libz.so
bin/voreenve: /opt/Qt5.1.0/5.1.0/gcc_64/lib/libQt5Svg.so.5.1.0
bin/voreenve: /opt/Qt5.1.0/5.1.0/gcc_64/lib/libQt5Widgets.so.5.1.0
bin/voreenve: /opt/Qt5.1.0/5.1.0/gcc_64/lib/libQt5Gui.so.5.1.0
bin/voreenve: /opt/Qt5.1.0/5.1.0/gcc_64/lib/libQt5Core.so.5.1.0
bin/voreenve: apps/voreenve/CMakeFiles/voreenve.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/voreenve"
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/voreenve.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
apps/voreenve/CMakeFiles/voreenve.dir/build: bin/voreenve
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/build

apps/voreenve/CMakeFiles/voreenve.dir/requires: apps/voreenve/CMakeFiles/voreenve.dir/main.cpp.o.requires
apps/voreenve/CMakeFiles/voreenve.dir/requires: apps/voreenve/CMakeFiles/voreenve.dir/voreenmainwindow.cpp.o.requires
apps/voreenve/CMakeFiles/voreenve.dir/requires: apps/voreenve/CMakeFiles/voreenve.dir/voreenmoduleve.cpp.o.requires
apps/voreenve/CMakeFiles/voreenve.dir/requires: apps/voreenve/CMakeFiles/voreenve.dir/voreenveapplication.cpp.o.requires
apps/voreenve/CMakeFiles/voreenve.dir/requires: apps/voreenve/CMakeFiles/voreenve.dir/voreenveplugin.cpp.o.requires
apps/voreenve/CMakeFiles/voreenve.dir/requires: apps/voreenve/CMakeFiles/voreenve.dir/voreenvisualization.cpp.o.requires
apps/voreenve/CMakeFiles/voreenve.dir/requires: apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenmainwindow.cpp.o.requires
apps/voreenve/CMakeFiles/voreenve.dir/requires: apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenveapplication.cpp.o.requires
apps/voreenve/CMakeFiles/voreenve.dir/requires: apps/voreenve/CMakeFiles/voreenve.dir/moc_voreenvisualization.cpp.o.requires
apps/voreenve/CMakeFiles/voreenve.dir/requires: apps/voreenve/CMakeFiles/voreenve.dir/qrc_voreenve.cpp.o.requires
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/requires

apps/voreenve/CMakeFiles/voreenve.dir/clean:
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve && $(CMAKE_COMMAND) -P CMakeFiles/voreenve.dir/cmake_clean.cmake
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/clean

apps/voreenve/CMakeFiles/voreenve.dir/depend: apps/voreenve/moc_voreenmainwindow.cpp
apps/voreenve/CMakeFiles/voreenve.dir/depend: apps/voreenve/moc_voreenveapplication.cpp
apps/voreenve/CMakeFiles/voreenve.dir/depend: apps/voreenve/moc_voreenvisualization.cpp
apps/voreenve/CMakeFiles/voreenve.dir/depend: apps/voreenve/qrc_voreenve.cpp
	cd /home/emma/code/gitrepo/voreen-src-4.3-unix && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/emma/code/gitrepo/voreen-src-4.3-unix /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve /home/emma/code/gitrepo/voreen-src-4.3-unix /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve /home/emma/code/gitrepo/voreen-src-4.3-unix/apps/voreenve/CMakeFiles/voreenve.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : apps/voreenve/CMakeFiles/voreenve.dir/depend
