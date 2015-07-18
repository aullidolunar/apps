# ./CMakeLists.txt

# Defaults
# -DENABLE_DEBUG=OFF
# -DENABLE_MAINTAINER=OFF
# -DCMAKE_INSTALL_PREFIX=/usr/local

# *nix
# cmake -DENABLE_MAINTAINER=ON -DENABLE_DEBUG=ON -DCMAKE_INSTALL_PREFIX= ..
# Windows 
# cmake -DENABLE_MAINTAINER=ON -DENABLE_DEBUG=ON -DCMAKE_INSTALL_PREFIX= ..

# Tell not to build from source directory
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message (FATAL_ERROR "It is best, not to build from toplevel directory. Create and go to \"build\" directory and run from there")
endif ()

# toolkit
set (_PT "qt4")
# package name
set (_PN "alarm")
# package version
set (_PV "2.0")
# package rev number
set (_PR "0")
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

if (NOT MSVC)
	include (CheckCXXCompilerFlag)
	check_cxx_compiler_flag ("-std=c++11" COMPILER_SUPPORTS_CXX11)
	if (${COMPILER_SUPPORTS_CXX11})
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
	else ()
		message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
	endif()
endif ()

# test if we are in win32
if (WIN32)
	set (USER_OS "WIN32")
else ()
	set (USER_OS "UNIX")
endif ()
message (STATUS "OS: ${USER_OS}")

# Globally define unicode
add_definitions (-DUNICODE -D_UNICODE)

option (ENABLE_DEBUG "Enable debug mode messages" OFF)
if (ENABLE_DEBUG)
	set (CMAKE_BUILD_TYPE "Debug")
	add_definitions (-DENABLE_DEBUG -D_DEBUG -DDEBUG)
else ()
	set (CMAKE_BUILD_TYPE "Release")
	add_definitions (-DNDEBUG)
	if (WIN32 AND MINGW)
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
	endif ()
endif ()
message (STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if (WIN32)
# do win32 stuff ¬.¬
	set (_PROJECT_INSTALL_DIR "${PROJECT_NAME}")
else ()
	# linux home sweet home stuff :v
	set (_PROJECT_INSTALL_DIR "bin")
endif ()

option (ENABLE_MAINTAINER "Enable maintainer mode (locally testing)" OFF)
if (ENABLE_MAINTAINER)
	set (DATA_DIR "${PROJECT_SOURCE_DIR}/data")
	set (LOCALEDIR "${PROJECT_BINARY_DIR}/locales")
else ()
	if (WIN32)
		set (DATA_DIR "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}")
	else ()
		set (DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}")
	endif ()
	set (LOCALEDIR "${DATA_DIR}/locales")
endif ()
message (STATUS "Maintainer mode: ${ENABLE_MAINTAINER}")

# add this directory in our include search path
include_directories ("${PROJECT_BINARY_DIR}" ${PROJECT_BINARY_DIR}/src)

# just for the sanity of the project
if (EXISTS "${PROJECT_SOURCE_DIR}/src/config.h.in")
	configure_file ("${PROJECT_SOURCE_DIR}/src/config.h.in" "${PROJECT_BINARY_DIR}/config.h")
	add_definitions (-DHAVE_CONFIG_H)
endif ()

if (EXISTS "${PROJECT_SOURCE_DIR}/data/CMakeLists.txt")
	add_subdirectory (data)
endif ()

if (EXISTS "${PROJECT_SOURCE_DIR}/locales/CMakeLists.txt")
	add_subdirectory (locales)
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
		COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/${_PLN}/locales
		COMMAND ${CMAKE_COMMAND} -E copy_directory locales ${PROJECT_BINARY_DIR}/${_PLN}/locales
		COMMAND ${7Z} a -t7z ${PROJECT_BINARY_DIR}/${PACKER_PACKAGE_FILE_NAME} ${PROJECT_BINARY_DIR}/${_PLN}
		COMMAND ${CMAKE_COMMAND} -E remove_directory "${PROJECT_BINARY_DIR}/${_PLN}"
		COMMENT "${PACKER_PACKAGE_FILE_NAME} created"
	)
else (7Z)
	message (STATUS "Package 7z: Not found (targets dist will be not created)")
endif (7Z)

# EOF :~
