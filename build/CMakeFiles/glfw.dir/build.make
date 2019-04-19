# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/psy/Documentos/GitProjects/icmc-cg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/psy/Documentos/GitProjects/icmc-cg/build

# Utility rule file for glfw.

# Include the progress variables for this target.
include CMakeFiles/glfw.dir/progress.make

CMakeFiles/glfw: CMakeFiles/glfw-complete


CMakeFiles/glfw-complete: glfw/src/glfw-stamp/glfw-install
CMakeFiles/glfw-complete: glfw/src/glfw-stamp/glfw-mkdir
CMakeFiles/glfw-complete: glfw/src/glfw-stamp/glfw-download
CMakeFiles/glfw-complete: glfw/src/glfw-stamp/glfw-update
CMakeFiles/glfw-complete: glfw/src/glfw-stamp/glfw-patch
CMakeFiles/glfw-complete: glfw/src/glfw-stamp/glfw-configure
CMakeFiles/glfw-complete: glfw/src/glfw-stamp/glfw-build
CMakeFiles/glfw-complete: glfw/src/glfw-stamp/glfw-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/psy/Documentos/GitProjects/icmc-cg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'glfw'"
	/usr/bin/cmake -E make_directory /home/psy/Documentos/GitProjects/icmc-cg/build/CMakeFiles
	/usr/bin/cmake -E touch /home/psy/Documentos/GitProjects/icmc-cg/build/CMakeFiles/glfw-complete
	/usr/bin/cmake -E touch /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-done

glfw/src/glfw-stamp/glfw-install: glfw/src/glfw-stamp/glfw-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/psy/Documentos/GitProjects/icmc-cg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing install step for 'glfw'"
	cd /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-build && /usr/bin/cmake -Dmake=$(MAKE) -P /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-install-.cmake
	cd /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-build && /usr/bin/cmake -E touch /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-install

glfw/src/glfw-stamp/glfw-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/psy/Documentos/GitProjects/icmc-cg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Creating directories for 'glfw'"
	/usr/bin/cmake -E make_directory /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw
	/usr/bin/cmake -E make_directory /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-build
	/usr/bin/cmake -E make_directory /home/psy/Documentos/GitProjects/icmc-cg/build/glfw
	/usr/bin/cmake -E make_directory /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/tmp
	/usr/bin/cmake -E make_directory /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp
	/usr/bin/cmake -E make_directory /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src
	/usr/bin/cmake -E touch /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-mkdir

glfw/src/glfw-stamp/glfw-download: glfw/src/glfw-stamp/glfw-gitinfo.txt
glfw/src/glfw-stamp/glfw-download: glfw/src/glfw-stamp/glfw-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/psy/Documentos/GitProjects/icmc-cg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'glfw'"
	cd /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src && /usr/bin/cmake -P /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-download-.cmake
	cd /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src && /usr/bin/cmake -E touch /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-download

glfw/src/glfw-stamp/glfw-update: glfw/src/glfw-stamp/glfw-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/psy/Documentos/GitProjects/icmc-cg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No update step for 'glfw'"
	cd /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw && /usr/bin/cmake -E echo_append
	cd /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw && /usr/bin/cmake -E touch /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-update

glfw/src/glfw-stamp/glfw-patch: glfw/src/glfw-stamp/glfw-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/psy/Documentos/GitProjects/icmc-cg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "No patch step for 'glfw'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-patch

glfw/src/glfw-stamp/glfw-configure: glfw/tmp/glfw-cfgcmd.txt
glfw/src/glfw-stamp/glfw-configure: glfw/src/glfw-stamp/glfw-update
glfw/src/glfw-stamp/glfw-configure: glfw/src/glfw-stamp/glfw-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/psy/Documentos/GitProjects/icmc-cg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Performing configure step for 'glfw'"
	cd /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-build && /usr/bin/cmake -P /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-configure-.cmake
	cd /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-build && /usr/bin/cmake -E touch /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-configure

glfw/src/glfw-stamp/glfw-build: glfw/src/glfw-stamp/glfw-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/psy/Documentos/GitProjects/icmc-cg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Performing build step for 'glfw'"
	cd /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-build && /usr/bin/cmake -Dmake=$(MAKE) -P /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-build-.cmake
	cd /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-build && /usr/bin/cmake -E touch /home/psy/Documentos/GitProjects/icmc-cg/build/glfw/src/glfw-stamp/glfw-build

glfw: CMakeFiles/glfw
glfw: CMakeFiles/glfw-complete
glfw: glfw/src/glfw-stamp/glfw-install
glfw: glfw/src/glfw-stamp/glfw-mkdir
glfw: glfw/src/glfw-stamp/glfw-download
glfw: glfw/src/glfw-stamp/glfw-update
glfw: glfw/src/glfw-stamp/glfw-patch
glfw: glfw/src/glfw-stamp/glfw-configure
glfw: glfw/src/glfw-stamp/glfw-build
glfw: CMakeFiles/glfw.dir/build.make

.PHONY : glfw

# Rule to build all files generated by this target.
CMakeFiles/glfw.dir/build: glfw

.PHONY : CMakeFiles/glfw.dir/build

CMakeFiles/glfw.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glfw.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glfw.dir/clean

CMakeFiles/glfw.dir/depend:
	cd /home/psy/Documentos/GitProjects/icmc-cg/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/psy/Documentos/GitProjects/icmc-cg /home/psy/Documentos/GitProjects/icmc-cg /home/psy/Documentos/GitProjects/icmc-cg/build /home/psy/Documentos/GitProjects/icmc-cg/build /home/psy/Documentos/GitProjects/icmc-cg/build/CMakeFiles/glfw.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glfw.dir/depend

