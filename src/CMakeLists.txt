# src/CMakeLists.txt

message (STATUS "+- entering SRC directory -+")

# set link flags
set (LINKER_FLAGS)

# sources
set (_SOURCES
	callbacks.c
	main.c
)

# search for pkg-config
include (FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
	message (FATAL_ERROR "pkg-config not found")
endif ()

# check for gtk
pkg_check_modules (GTK gtk+-${GTK_TOOLKIT_VERSION}>=${GTK_TOOLKIT_VERSION_NEED} REQUIRED)
if (NOT GTK_FOUND)
	message(FATAL_ERROR "You don't seem to have gtk+-${GTK_TOOLKIT_VERSION} development libraries version ${GTK_TOOLKIT_VERSION_NEED} or better installed")
else ()
	include_directories (${GTK_INCLUDE_DIRS})
	link_directories (${GTK_LIBRARY_DIRS})
	link_libraries (${GTK_LIBRARIES})
	set (LINKER_FLAGS ${LINKER_FLAGS} ${GTK_LINK_FLAGS})
endif ()

# target creation
include_directories (${PROJECT_BINARY_DIR})
add_executable (${PROJECT_NAME} ${_SOURCES} ${LINKER_FLAGS})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# install destination
install (TARGETS ${PROJECT_NAME} DESTINATION "bin")
