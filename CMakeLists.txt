# ./CMakeLists.txt

# Defaults
# -DENABLE_DEBUG=OFF
# -DENABLE_MAINTAINER=OFF
# -DCMAKE_INSTALL_PREFIX=/usr/local

# *nix
# cmake -DENABLE_DEBUG=ON -DENABLE_MAINTAINER=ON -DCMAKE_INSTALL_PREFIX= ..
# Windows (msys)
# cmake -G "MSYS Makefiles" -DENABLE_DEBUG=ON -DENABLE_MAINTAINER=ON -DCMAKE_INSTALL_PREFIX= ..

# Tell not to build from source directory
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message (FATAL_ERROR "It is best, not to build from toplevel directory. Create and go to \"build\" directory and run from there")
endif ()

# toolkit
set (_PT "gtkmm2")
# package name
set (_PN "alarm")
# package version
set (_PV "1.0")
# package rev number
set (_PR "1")
# package long name
set (_PLN "${_PT}-${_PN}-${_PV}")
# package long version 
set (_PLV "${_PLN}rev${_PR}")
# me
set (AUTHOR "Joel Almeida")
# moar me
set (EMAIL "aullidolunar@gmail.com")
# packer name
set (PACKER_PACKAGE_FILE_NAME "${_PLV}-src.7z")

cmake_minimum_required (VERSION 3.0)
project ("${_PN}" VERSION "${_PV}" LANGUAGES CXX)
# welcome message
message (STATUS "Starting building process for ${PROJECT_NAME} version ${_PV} rev ${_PR}")

include (CheckCXXCompilerFlag)
check_cxx_compiler_flag ("-std=gnu++11" COMPILER_SUPPORTS_CXX11)
if (${COMPILER_SUPPORTS_CXX11})
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    message (STATUS "${CMAKE_CXX_COMPILER} supports C++11: Yes")
else ()
    message(FATAL_ERROR "${CMAKE_CXX_COMPILER} doesn't support C++11 (required)")
endif()
if (WIN32)
	check_cxx_compiler_flag ("-Wno-literal-suffix" COMPILER_SUPPORTS_NO_LITERAL_SUFFIX)
	if (${COMPILER_SUPPORTS_NO_LITERAL_SUFFIX})
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-literal-suffix")
	endif ()
endif ()

# test if we are in win32
if (WIN32)
# do win32 stuff ¬.¬
	set (_PROJECT_INSTALL_DIR "${PROJECT_NAME}")
	set (_PROJECT_DATA_DIR_NOMAINTAINER "${CMAKE_INSTALL_PREFIX}")
	set (_PROJECT_DATA_DIR_DOMAINTAINER "${PROJECT_SOURCE_DIR}/data")
	set (LOCALE_PREFIX "${PROJECT_NAME}/locale")
	add_definitions (-DIN_WIN32)
	set (USER_OS "WIN32")
else ()
	# linux home sweet home stuff :v
	set (_PROJECT_INSTALL_DIR "bin")
	set (_PROJECT_DATA_DIR_NOMAINTAINER "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}")
	set (_PROJECT_DATA_DIR_DOMAINTAINER "${PROJECT_SOURCE_DIR}/data")
	set (LOCALE_PREFIX "share/${PROJECT_NAME}/locale")
	set (USER_OS "UNIX")
endif ()

message (STATUS "OS: ${USER_OS}")

option (ENABLE_DEBUG "Enable debug mode" OFF)
if (${ENABLE_DEBUG})
	set (CMAKE_BUILD_TYPE "Debug")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -O0")
	add_definitions (-DENABLE_DEBUG -D_DEBUG)
else ()
	set (CMAKE_BUILD_TYPE "Release")
	set (CMAKE_CXXFLAGS "${CMAKE_CXX_FLAGS} -Os")
endif ()

message (STATUS "Build mode: ${CMAKE_BUILD_TYPE}")

option (ENABLE_MAINTAINER "Enable maintainer mode (locally testing)" OFF)
set (DATA_DIR "${_PROJECT_DATA_DIR_DOMAINTAINER}")
if (${ENABLE_MAINTAINER})
	set (DATA_DIR "${_PROJECT_DATA_DIR_DOMAINTAINER}")
	set (LOCALEDIR "${PROJECT_BINARY_DIR}/locale")
else ()
	set (DATA_DIR "${_PROJECT_DATA_DIR_NOMAINTAINER}")
	set (LOCALEDIR "${DATA_DIR}/locale")
endif ()

message (STATUS "Maintainer mode: ${ENABLE_MAINTAINER}")

# add this directory in our include path
include_directories ("${PROJECT_BINARY_DIR}")

# just for the sanity of the project
if (EXISTS "${PROJECT_SOURCE_DIR}/src/config.h.in")
	configure_file ("${PROJECT_SOURCE_DIR}/src/config.h.in" "${PROJECT_BINARY_DIR}/config.h")
	add_definitions (-DHAVE_CONFIG_H)
endif ()

if (EXISTS "${PROJECT_SOURCE_DIR}/data/CMakeLists.txt")
	add_subdirectory (data)
endif ()

if (EXISTS "${PROJECT_SOURCE_DIR}/po/CMakeLists.txt")
	add_subdirectory (po)
endif ()

add_subdirectory (src)

# do local test
add_custom_target (run COMMAND ${PROJECT_BINARY_DIR}/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX} DEPENDS ${PROJECT_NAME})

# clean stuff: TODO: fixme and make me windows <-> *nix platform indepedent
# add_custom_target (distclean COMMAND rm -rf *)
# workaround
set_directory_properties (PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "config.h;CMakeCache.txt;${PROJECT_NAME};${PACKER_PACKAGE_FILE_NAME}")

# archive the source code
find_program (7Z 7za NAMES 7z)
if (7Z)
	message (STATUS "Program 7z: ${7Z} (targets dist is created)")
	add_custom_target (
		dist
		COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/${_PLN}"
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		COMMAND ${CMAKE_COMMAND} -E copy CMakeLists.txt ${PROJECT_BINARY_DIR}/${_PLN}
		COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/${P_PLN}/src
		COMMAND ${CMAKE_COMMAND} -E copy_directory src ${PROJECT_BINARY_DIR}/${_PLN}/src
		COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/${_PLN}/data
		COMMAND ${CMAKE_COMMAND} -E copy_directory data ${PROJECT_BINARY_DIR}/${_PLN}/data
		COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/${_PLN}/po
		COMMAND ${CMAKE_COMMAND} -E copy_directory po ${PROJECT_BINARY_DIR}/${_PLN}/po
		COMMAND ${7Z} a -t7z ${PROJECT_BINARY_DIR}/${PACKER_PACKAGE_FILE_NAME} ${PROJECT_BINARY_DIR}/${_PLN}
		COMMAND ${CMAKE_COMMAND} -E remove_directory "${PROJECT_BINARY_DIR}/${_PLN}"
		COMMENT "${PACKER_PACKAGE_FILE_NAME} created"
	)
else (7Z)
	message (STATUS "Package 7z: Not found (targets dist will be not created)")
endif (7Z)

# EOF :~
