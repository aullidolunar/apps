# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.1

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
CMAKE_SOURCE_DIR = /home/joel/Documentos/gcc/gtk2-youtubedl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joel/Documentos/gcc/gtk2-youtubedl/build

# Utility rule file for create-po.

# Include the progress variables for this target.
include po/CMakeFiles/create-po.dir/progress.make

po/CMakeFiles/create-po:
	cd /home/joel/Documentos/gcc/gtk2-youtubedl/build/po && /bin/msginit --no-translator --no-wrap -i /home/joel/Documentos/gcc/gtk2-youtubedl/build/gtk2-youtubedl.pot -o /home/joel/Documentos/gcc/gtk2-youtubedl/po/es.po -l es_MX.utf8

create-po: po/CMakeFiles/create-po
create-po: po/CMakeFiles/create-po.dir/build.make
.PHONY : create-po

# Rule to build all files generated by this target.
po/CMakeFiles/create-po.dir/build: create-po
.PHONY : po/CMakeFiles/create-po.dir/build

po/CMakeFiles/create-po.dir/clean:
	cd /home/joel/Documentos/gcc/gtk2-youtubedl/build/po && $(CMAKE_COMMAND) -P CMakeFiles/create-po.dir/cmake_clean.cmake
.PHONY : po/CMakeFiles/create-po.dir/clean

po/CMakeFiles/create-po.dir/depend:
	cd /home/joel/Documentos/gcc/gtk2-youtubedl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joel/Documentos/gcc/gtk2-youtubedl /home/joel/Documentos/gcc/gtk2-youtubedl/po /home/joel/Documentos/gcc/gtk2-youtubedl/build /home/joel/Documentos/gcc/gtk2-youtubedl/build/po /home/joel/Documentos/gcc/gtk2-youtubedl/build/po/CMakeFiles/create-po.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : po/CMakeFiles/create-po.dir/depend

