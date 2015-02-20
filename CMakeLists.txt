# ./CMakeLists.txt

# Defaults
# -DENABLE_DEBUG=OFF
# -DENABLE_MAINTAINER=OFF
# -DCMAKE_INSTALL_PREFIX=/usr/local

# cmake -DENABLE_DEBUG=ON -DENABLE_MAINTAINER=ON ../

cmake_minimum_required (VERSION 3.0)
project ("calaca02" VERSION "1.0" LANGUAGES CXX)
set (AUTHOR "Joel Almeida García")
set (EMAIL "aullidolunar@gmail.com")

include (CheckCXXCompilerFlag)
check_cxx_compiler_flag ("-std=c++11" COMPILER_SUPPORTS_CXX11)
if (${COMPILER_SUPPORTS_CXX11})
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else ()
    message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
endif()

find_program (YOUTUBEDL_PATH "youtube-dl")
if (${YOUTUBEDL_PATH-NOTFOUND})
	message(FATAL_ERROR "youtube-dl wasn't found (required).")
endif ()

option (ENABLE_DEBUG "Enable debug mode" OFF)
if (${ENABLE_DEBUG})
	set (CMAKE_BUILD_TYPE "Debug")
	message (STATUS "*** Compiling in debug mode ***")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -O0")
	add_definitions (-DENABLE_DEBUG)
else ()
	message (STATUS "*** Compiling in release mode ***")
	set (CMAKE_BUILD_TYPE "Release")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
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

configure_file ("${PROJECT_SOURCE_DIR}/src/config.h.in" "${PROJECT_BINARY_DIR}/config.h")
add_definitions (-DHAVE_CONFIG_H)

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
