# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fais/punk.systems/code/c/qtWispr

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fais/punk.systems/code/c/qtWispr/build

# Utility rule file for qtWispr_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/qtWispr_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/qtWispr_autogen.dir/progress.make

CMakeFiles/qtWispr_autogen: qtWispr_autogen/timestamp

qtWispr_autogen/timestamp: /usr/lib/qt6/moc
qtWispr_autogen/timestamp: /usr/lib/qt6/uic
qtWispr_autogen/timestamp: CMakeFiles/qtWispr_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/fais/punk.systems/code/c/qtWispr/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target qtWispr"
	/usr/bin/cmake -E cmake_autogen /home/fais/punk.systems/code/c/qtWispr/build/CMakeFiles/qtWispr_autogen.dir/AutogenInfo.json ""
	/usr/bin/cmake -E touch /home/fais/punk.systems/code/c/qtWispr/build/qtWispr_autogen/timestamp

qtWispr_autogen: CMakeFiles/qtWispr_autogen
qtWispr_autogen: qtWispr_autogen/timestamp
qtWispr_autogen: CMakeFiles/qtWispr_autogen.dir/build.make
.PHONY : qtWispr_autogen

# Rule to build all files generated by this target.
CMakeFiles/qtWispr_autogen.dir/build: qtWispr_autogen
.PHONY : CMakeFiles/qtWispr_autogen.dir/build

CMakeFiles/qtWispr_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qtWispr_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qtWispr_autogen.dir/clean

CMakeFiles/qtWispr_autogen.dir/depend:
	cd /home/fais/punk.systems/code/c/qtWispr/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fais/punk.systems/code/c/qtWispr /home/fais/punk.systems/code/c/qtWispr /home/fais/punk.systems/code/c/qtWispr/build /home/fais/punk.systems/code/c/qtWispr/build /home/fais/punk.systems/code/c/qtWispr/build/CMakeFiles/qtWispr_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/qtWispr_autogen.dir/depend

