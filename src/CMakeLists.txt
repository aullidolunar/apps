# src/CMakeLists.txt

# linker flags
set (LINKER_FLAGS)

# linker libs
set (LINKER_LIBS)

# sources
set (_SOURCES notify.cc alarm_frm.cc main.cc)

# search for gtkmm2
set (TOOLKIT_VERSION_NEED "2.20")
include (FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
	message (FATAL_ERROR "pkg-config not found")
endif ()

pkg_check_modules (GTKMM2 REQUIRED QUIET gtkmm-2.4>=${TOOLKIT_VERSION_NEED} )
if (NOT GTKMM2_FOUND)
	message (FATAL_ERROR "gtkmm2 development files not found")
else ()
	include_directories (${GTKMM2_INCLUDE_DIRS})
	link_directories (${GTKMM2_LIBRARY_DIRS})
	set (LINKER_LIBS ${LINKER_LIBS} ${GTKMM2_LIBRARIES})
	set (LINKER_FLAGS ${LINKER_FLAGS} ${GTKMM2_LINK_FLAGS})
	message (STATUS "Need gtkmm2 ${TOOLKIT_VERSION_NEED}: Found (have ${gtkmm2_VERSION})")
endif ()

# Try to find libnotifymm >= 0.6 for notifications, if not use inner ugly dialog notification -_-
pkg_search_module (LIBNOTIFYMM QUIET libnotifymm-1.0>=0.6)
if (LIBNOTIFYMM_FOUND)
	add_definitions (-DHAVE_NOTIFYMM)
	include_directories (${LIBNOTIFYMM_INCLUDE_DIRS})
	link_directories (${LIBNOTIFYMM_LIBRARY_DIRS})
	set (LINKER_LIBS ${LINKER_LIBS} ${LIBNOTIFYMM_LIBRARIES})
	set (LINKER_FLAGS ${LINKER_FLAGS} ${LIBNOTIFYMM_LINK_FLAGS})
	message (STATUS "Need libnotifymm 0.6: found (have ${LIBNOTIFYMM_VERSION})")
else ()
	message (STATUS "libnotifymm: Not found")
endif ()

# find sdl2
pkg_check_modules (SDL2 REQUIRED QUIET sdl2)
if (NOT SDL2_FOUND)
	message (FATAL_ERROR "sdl2 development files not found")
else ()
	include_directories (${SDL2_INCLUDE_DIRS})
	link_directories (${SDL2_LIBRARY_DIRS})
	set (LINKER_LIBS ${LINKER_LIBS} ${SDL2_LIBRARIES})
	set (LINKER_FLAGS ${LINKER_FLAGS} ${SDL2_LINK_FLAGS})
	message (STATUS "sdl2: Found")
endif ()

# SDL2_mixer
pkg_check_modules (SDL2_MIXER REQUIRED QUIET SDL2_mixer)
if (NOT SDL2_MIXER_FOUND)
	message (FATAL_ERROR "sdl2_mixer development files not found")
else ()
	include_directories (${SDL2_MIXER_INCLUDE_DIRS})
	link_directories (${SDL2_MIXER_LIBRARY_DIRS})
	set (LINKER_LIBS ${LINKER_LIBS} ${SDL2_MIXER_LIBRARIES})
	set (LINKER_FLAGS ${LINKER_FLAGS} ${SDL2_MIXER_LINK_FLAGS})
	message (STATUS "SDL2_mixer: Found")
endif ()

# locate RC and let's do our best here in win32 to add the resource file
if (EXISTS "${PROJECT_SOURCE_DIR}/src/resource.rc.in" AND WIN32)
	find_program(RC_PATH windres)
	if (NOT RC_PATH)
		message (FATAL_ERROR "RC not found (required)")
	endif ()
	set (RESOURCE_FILE_IN "${PROJECT_SOURCE_DIR}/src/resource.rc.in")
	set (RESOURCE_FILE_OUT "${PROJECT_BINARY_DIR}/resource.rc")
	set (RESOURCE_OBJECT "${PROJECT_BINARY_DIR}/resource.o")
	configure_file ("${RESOURCE_FILE_IN}" "${RESOURCE_FILE_OUT}")
	add_custom_command (
		OUTPUT ${RESOURCE_OBJECT}
		COMMAND ${RC_PATH} -I${PROJECT_SOURCE_DIR}/src -I${PROJECT_BINARY_DIR} "${RESOURCE_FILE_OUT}" -o "${RESOURCE_OBJECT}"
		COMMENT "Compiling resource file"
	)
	add_custom_target (resourcefile DEPENDS ${RESOURCE_OBJECT})
	set_source_files_properties (${RESOURCE_OBJECT} PROPERTIES EXTERNAL_OBJECT true GENERATED true)
	set (_SOURCES ${_SOURCES} ${RESOURCE_OBJECT})
endif ()

# target creation
add_executable (${PROJECT_NAME} ${_SOURCES} ${LINKER_FLAGS})
# well, it works!! =)
if (TARGET resourcefile AND WIN32)
	add_dependencies (${PROJECT_NAME} resourcefile)
endif ()
target_link_libraries (${PROJECT_NAME} ${LINKER_LIBS})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# install destination
install (TARGETS ${PROJECT_NAME} DESTINATION "${_PROJECT_INSTALL_DIR}")
