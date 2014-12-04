# src/CMakeLists.txt

# set link flags
set (LINKER_FLAGS)

# sources
set (_SOURCES
	notify.c
	helper.c
	page1.c
	page2.c
	status-icon.c
	sound.c
	timer.c
	main-window.c
	main.c
)

# search for pkg-config
include (FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
	message (FATAL_ERROR "pkg-config not found")
endif (NOT PKG_CONFIG_FOUND)

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

# check for canberra
pkg_check_modules (CANBERRA ${LIBCANBERRA_GTK}>=${LIBCANBERRA_GTK_VERSION_NEED} REQUIRED)
if (NOT CANBERRA_FOUND)
	message(FATAL_ERROR "You don't seem to have ${LIBCANBERRA_GTK} development libraries version ${LIBCANBERRA_GTK_VERSION_NEED} or better installed")
else ()
	include_directories (${CANBERRA_INCLUDE_DIRS})
	link_directories (${CANBERRA_LIBRARY_DIRS})
	link_libraries (${CANBERRA_LIBRARIES})
	set (LINKER_FLAGS ${LINKER_FLAGS} ${CANBERRA_LINK_FLAGS})
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
		set (_SOURCES ${_SOURCES} notify.c)
	endif ()
endif ()

# target creation
include_directories (${PROJECT_BINARY_DIR})
add_executable (${PROJECT_NAME} ${_SOURCES} ${LINKER_FLAGS})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# install destination
install (TARGETS ${PROJECT_NAME} DESTINATION "bin")
