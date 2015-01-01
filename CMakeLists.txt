# ./CMakeLists.txt

# Defaults
# -DENABLE_DEBUG=OFF
# -DENABLE_MAINTAINER=OFF
# -DCMAKE_INSTALL_PREFIX=/usr/local

# cmake -DENABLE_DEBUG=ON -DENABLE_MAINTAINER=ON ../

cmake_minimum_required (VERSION 3.0)
project ("gtk2-percentage" VERSION "1.0" LANGUAGES C)
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
	set (RES_DIR "${PROJECT_SOURCE_DIR}/data")
	set (LOCALEDIR "${PROJECT_BINARY_DIR}/locale")
else ()
	set (RES_DIR "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}")
	set (LOCALEDIR "${RES_DIR}/locale")
endif ()

set (GTK_TOOLKIT_VERSION "2.0")
set (GTK_TOOLKIT_VERSION_NEED "2.24")

configure_file (
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)
add_definitions (-DHAVE_CONFIG_H)

enable_testing ()

add_subdirectory (src)

if (EXISTS "${PROJECT_SOURCE_DIR}/data")
	add_subdirectory (data)
endif ()

if (EXISTS "${PROJECT_SOURCE_DIR}/po")
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
