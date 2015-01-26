# ./CMakeLists.txt

# Defaults
# -DENABLE_DEBUG=OFF
# -DENABLE_MAINTAINER=OFF
# -DCMAKE_INSTALL_PREFIX=/usr/local

# cmake -DENABLE_DEBUG=ON -DENABLE_MAINTAINER=ON -DWITH_LIBNOTIFY=ON ../

cmake_minimum_required (VERSION 3.0)
project ("gtk2-alarm" VERSION "1.0" LANGUAGES C)
set (AUTHOR "Joel Almeida García")
set (EMAIL "aullidolunar@gmail.com")

option (ENABLE_DEBUG "Enable debug mode" OFF)
if (${ENABLE_DEBUG})
	set (CMAKE_BUILD_TYPE "Debug")
	message (STATUS "*** Compiling in debug mode ***")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -O0")
	add_definitions (-DENABLE_DEBUG)
else ()
	message (STATUS "*** Compiling in release mode ***")
	set (CMAKE_BUILD_TYPE "Release")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os")
endif ()

option (ENABLE_MAINTAINER "Enable maintainer mode (locally testing)" OFF)
if (${ENABLE_MAINTAINER})
	message (STATUS "*** Maintainer mode is enabled ***")
	set (DATA_DIR "${PROJECT_SOURCE_DIR}/data")
	set (LOCALEDIR "${PROJECT_BINARY_DIR}/locale")
else ()
	set (DATA_DIR "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}")
	set (LOCALEDIR "${DATA_DIR}/locale")
endif ()

option (WITH_LIBNOTIFY "Link with libnotfy" ON)
if (${WITH_LIBNOTIFY})
	message (STATUS "*** With libnotify ***")
	set (NOTIFY_VERSION_NEED "0.6")
	add_definitions (-DWITH_LIBNOTIFY)
endif ()

configure_file (
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)
add_definitions (-DHAVE_CONFIG_H)

set (GTK_TOOLKIT_VERSION_NEED "2.20")
set (LIBCANBERRA_VERSION_NEED "0.24")

# set link flags
set (LINKER_FLAGS)

# sources
set (_SOURCES
	helpers.c
	callbacks.c
	main.c
)

# search for pkg-config
include (FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
	message (FATAL_ERROR "pkg-config not found")
endif ()

# check for gtk
pkg_check_modules (GTK2 gtk+-2.0>=${GTK_TOOLKIT_VERSION_NEED} REQUIRED)
if (NOT GTK2_FOUND)
	message(FATAL_ERROR "You don't seem to have gtk+-${GTK_TOOLKIT_VERSION} development libraries version ${GTK_TOOLKIT_VERSION_NEED} or better installed")
else ()
	include_directories (${GTK2_INCLUDE_DIRS})
	link_directories (${GTK2_LIBRARY_DIRS})
	link_libraries (${GTK2_LIBRARIES})
	set (LINKER_FLAGS ${LINKER_FLAGS} ${GTK2_LINK_FLAGS})
endif ()

# check for libcanberra
pkg_check_modules (CANBERRA_GTK2 libcanberra-gtk>=${LIBCANBERRA_VERSION_NEED} REQUIRED)
if (NOT CANBERRA_GTK2_FOUND)
	message(FATAL_ERROR "You don't seem to have libcanberra-gtk development libraries version ${LIBCANBERRA_VERSION_NEED} or better installed")
else ()
	include_directories (${CANBERRA_GTK2_INCLUDE_DIRS})
	link_directories (${CANBERRA_GTK2_LIBRARY_DIRS})
	link_libraries (${CANBERRA_GTK2_LIBRARIES})
	set (LINKER_FLAGS ${LINKER_FLAGS} ${CANBERRA_GTK2_LINK_FLAGS})
endif ()

# check for libnotify
if (${WITH_LIBNOTIFY})
	pkg_check_modules (NOTIFY libnotify>=${NOTIFY_VERSION_NEED})
	if (NOT NOTIFY_FOUND)
		message(FATAL_ERROR "You don't seem to have libnotify development libraries version ${NOTIFY_VERSION_NEED} or better installed")
	else ()
		include_directories (${NOTIFY_INCLUDE_DIRS})
		link_directories (${NOTIFY_LIBRARY_DIRS})
		link_libraries (${NOTIFY_LIBRARIES})
		set (LINKER_FLAGS ${LINKER_FLAGS} ${NOTIFY_LINK_FLAGS})
	endif ()
endif ()

enable_testing ()

include_directories (${PROJECT_BINARY_DIR})

add_subdirectory (src)

if (EXISTS "${PROJECT_SOURCE_DIR}/data/CMakeLists.txt")
	add_subdirectory (data)
endif ()

if (EXISTS "${PROJECT_SOURCE_DIR}/po/CMakeLists.txt")
	add_subdirectory (po)
endif ()

add_test (
	NAME test
    COMMAND ${PROJECT_BINARY_DIR}/${PROJECT_NAME}
)

add_custom_target (run
	COMMAND ${PROJECT_BINARY_DIR}/${PROJECT_NAME}
	DEPENDS ${PROJECT_NAME}
)

add_custom_target (distclean
	COMMAND rm -rf *
)

add_custom_target(dist
	COMMAND tar -cvzf ../${PROJECT_NAME}-${PROJECT_VERSION}.tar.gz ../CMakeLists.txt ../src ../data ../po
)
