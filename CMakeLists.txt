# ./CMakeLists.txt

# Defaults
# -DENABLE_DEBUG=OFF
# -DENABLE_MAINTAINER=OFF
# -DWITH_GTK2=ON
# -DWITH_LIBNOTIFY=ON
# -DCMAKE_INSTALL_PREFIX=/usr/local

# cmake -DENABLE_DEBUG=ON -DENABLE_MAINTAINER=ON -DWITH_LIBNOTIFY=ON -DWITH_GTK2=ON ../

cmake_minimum_required (VERSION 3.0)
project ("galarm2" VERSION "1.0" LANGUAGES C)
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
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s")
endif ()

option (ENABLE_MAINTAINER "Enable maintainer mode (locally testing)" OFF)
if (${ENABLE_MAINTAINER})
	message (STATUS "*** Maintainer mode is enabled ***")
	set (RES_DIR "${PROJECT_SOURCE_DIR}/data")
	set (LOCALEDIR "${PROJECT_BINARY_DIR}/locale")
else ()
	set (RES_DIR "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}")
	set (LOCALEDIR "${RES_DIR}/locale")
endif ()

option (WITH_GTK2 "Enable or disable gtk+-2.0 toolkit" ON)
if (${WITH_GTK2})
	message (STATUS "*** Using gtk+-2.0 toolkit ***")
	add_definitions (-DWITH_GTK2)
	set (GTK_TOOLKIT_VERSION "2.0")
	set (GTK_TOOLKIT_VERSION_NEED "2.24")
	set (LIBCANBERRA_GTK "libcanberra-gtk")
	set (LIBCANBERRA_GTK_VERSION_NEED "0.28")
else ()
	message (STATUS "*** Using gtk+-3.0 toolkit ***")
	add_definitions (-DWITH_GTK3)
	set (GTK_TOOLKIT_VERSION "3.0")
	set (GTK_TOOLKIT_VERSION_NEED "3.12")
	set (LIBCANBERRA_GTK "libcanberra-gtk3")
	set (LIBCANBERRA_GTK_VERSION_NEED "0.28")
endif ()

option (WITH_LIBNOTIFY "Enable or disable libnotify" ON)
if (${WITH_LIBNOTIFY})
	message (STATUS "*** Enable libnotify ***")
	set (NOTIFY_VERSION_NEED "0.6")
	add_definitions (-DWITH_LIBNOTIFY)
endif ()

configure_file (
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)
add_definitions (-DHAVE_CONFIG_H)

enable_testing ()

add_subdirectory (src)
add_subdirectory (data)
# add_subdirectory (po)

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
