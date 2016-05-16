# Usage:
# cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_DEV=TRUE ..
# cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_DEV=TRUE ..
# cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DBUILD_DEV=TRUE ..

set (_PN "Alarma")
set (_PV "1.0.0.1")
set (_PD "Alarma")
set (AUTHOR "Joel Almeida")
set (EMAIL "aullidolunar@gmail.com")
set (PACKER_NAME "${_PN}-src")

cmake_minimum_required (VERSION 3.1)
project ("${_PN}" VERSION "${_PV}" LANGUAGES CXX)

# sources
list (APPEND _SOURCES frame.cxx main.cxx)
# wxWidgets components
list (APPEND _COMP adv media core base)

if (NOT CMAKE_BUILD_TYPE)
	set (CMAKE_BUILD_TYPE "Release")
endif ()

message ("-- Tipo de construir: ${CMAKE_BUILD_TYPE}")

option (BUILD_DEV "Build in developer mode" TRUE)
if (${BUILD_DEV})
	set (DATA_DIR "${PROJECT_SOURCE_DIR}")
else ()
	set (DATA_DIR "${CMAKE_INSTALL_PREFIX}/PROJECT_NAME")
endif ()
message ("-- Construir en modo desarrolador: ${BUILD_DEV}")

if (EXISTS "${PROJECT_SOURCE_DIR}/config.h.in")
	configure_file ("${PROJECT_SOURCE_DIR}/config.h.in" "${PROJECT_BINARY_DIR}/config.h")
	add_definitions (-DHAVE_CONFIG_H)
endif ()

# Localiza wxWidgets
if (UNIX)
	set (TOOLKIT_VERSION_NEED "3.0")
	set (wxWidgets_CONFIG_OPTIONS --version=${TOOLKIT_VERSION_NEED})
endif ()
find_package (wxWidgets COMPONENTS ${_COMP})
if (wxWidgets_FOUND)
	include (${wxWidgets_USE_FILE})
endif ()

# Resource
set (RESOURCE_FILE_IN "${PROJECT_SOURCE_DIR}/resource.rc.in")
if (EXISTS "${RESOURCE_FILE_IN}" AND MSVC)
	find_program(RC_PATH rc)
	if (NOT RC_PATH)
		message (FATAL_ERROR "RC.exe no encontrado")
	endif ()
	set (RESOURCE_OBJECT "${PROJECT_BINARY_DIR}/resource.RES")
	set (RESOURCE_FILE_OUT "${PROJECT_BINARY_DIR}/resource.rc")
	configure_file ("${RESOURCE_FILE_IN}" "${RESOURCE_FILE_OUT}")
	add_custom_command (OUTPUT "${RESOURCE_OBJECT}" 
		COMMAND ${RC_PATH} /I ${PROJECT_SOURCE_DIR} "${RESOURCE_FILE_OUT}"
		COMMENT "Compilando resource file")
	list (INSERT _SOURCES 0 ${RESOURCE_OBJECT})
	set_source_files_properties (${RESOURCE_OBJECT} PROPERTIES EXTERNAL_OBJECT true GENERATED true)
endif ()

include_directories ("${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")

add_executable (${PROJECT_NAME} ${_SOURCES})
list (APPEND _LIBS ${wxWidgets_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${_LIBS})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
if (MSVC)
	set_property (TARGET ${PROJECT_NAME} APPEND_STRING PROPERTY LINK_FLAGS "/SUBSYSTEM:WINDOWS /MANIFEST:NO /INCREMENTAL:NO")
	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif ()
add_custom_target (run COMMAND ${PROJECT_BINARY_DIR}/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX} DEPENDS ${PROJECT_NAME})
set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "resource.rc;config.h;CMakeCache.txt;cmake_install.cmake")

# EOF: ~
