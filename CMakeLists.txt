cmake_minimum_required (VERSION 3.0)
project (mtc VERSION "1.0" LANGUAGES CXX)
set (AUTHOR "Joel Almeida García" INTERNAL "Author")
set (EMAIL "aullidolunar@gmail.com")

set (PACKAGE ${PROJECT_NAME})
set (VERSION ${PROJECT_VERSION})
set (PACKAGE_BUGREPORT ${EMAIL})
set (LOCALEDIR ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME})

configure_file (
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)
add_definitions (-DHAVE_CONFIG_H)

# sources
set (_SOURCES src/mtc.cpp)

add_custom_target (run
	COMMAND ${PROJECT_BINARY_DIR}/${PROJECT_NAME}
	DEPENDS ../${PACKAGE}
)

add_custom_target (distclean
	COMMAND rm -rf *
)

add_custom_target(dist
	COMMAND tar -cvzf ../${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.tar.gz ../CMakeLists.txt ../src
)

include_directories (${PROJECT_BINARY_DIR})
add_executable (${PROJECT_NAME} ${_SOURCES})
install (TARGETS ${PROJECT_NAME} DESTINATION "bin")
