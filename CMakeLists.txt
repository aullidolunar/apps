# ./CMakeLists.txt
# -DCMAKE_BUILD_TYPE=Debug
# -DMAINTAINER_MODE=ON
# -DCMAKE_INSTALL_PREFIX=/usr

cmake_minimum_required (VERSION 3.0)
project (gtk2-youtubedl VERSION "1.1" LANGUAGES C)
set (AUTHOR "Joel Almeida García")
set (EMAIL "aullidolunar@gmail.com")

# find ffmpeg
find_program(F_PATH ffmpeg)
if (NOT F_PATH)
	message (FATAL_ERROR "ffmpeg not found (required)")
endif (NOT F_PATH)

# find youtube-dl
find_program(Y_PATH youtube-dl)
if (NOT Y_PATH)
	message (FATAL_ERROR "youtube-dl not found (required)")
endif (NOT Y_PATH)

# enable maintainer mode
# example -DMAINTAINER_MODE=ON
option (MAINTAINER_MODE "Enable maintainer mode (locally testing)" OFF)

if (${MAINTAINER_MODE} MATCHES ON)
	message (STATUS "*** Maintainer mode is enabled ***")
	set (RES_DIR "${PROJECT_SOURCE_DIR}/data")
	set (LOCALEDIR "${PROJECT_BINARY_DIR}/locale")
else ()
	set (RES_DIR "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}")
	set (LOCALEDIR "${RES_DIR}/locale")
endif ()

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
	message (STATUS "*** Compiling in debug mode ***")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -O0")
	add_definitions (-DDEBUG_ON)
else (${CMAKE_BUILD_TYPE} NOT MATCHES "Debug")
	message (STATUS "*** Compiling in release mode ***")
	set (CMAKE_BUILD_TYPE "Release")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s")
endif (${CMAKE_BUILD_TYPE} MATCHES "Debug")

configure_file (
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)
add_definitions (-DHAVE_CONFIG_H)

add_subdirectory (src)
add_subdirectory (data)
add_subdirectory (po)

add_custom_target (run
	COMMAND src/${PROJECT_NAME}
	DEPENDS ${PROJECT_NAME}
)

add_custom_target (distclean
	COMMAND rm -rf *
)

add_custom_target(dist
	COMMAND tar -cvzf ../${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.tar.gz ../CMakeLists.txt ../src ../data ../po
)
