# src/CMakeLists.txt

# search for pkg-config
include (FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
	message (FATAL_ERROR "pkg-config not found")
endif (NOT PKG_CONFIG_FOUND)

# check for gtk2
pkg_check_modules (GTK2 gtk+-2.0>=2.24 REQUIRED)
if (NOT GTK2_FOUND)
	message(FATAL_ERROR "You don't seem to have gtk+-2.0 development libraries installed")
endif (NOT GTK2_FOUND)

# check for vte 
pkg_check_modules (VTE2 vte>=0.24 REQUIRED)
if (NOT VTE2_FOUND)
	message(FATAL_ERROR "You don't seem to have vte (version for gtk+-2.0) development libraries installed")
endif (NOT VTE2_FOUND)

# sources
set (_SOURCES
	callbacks.c
	main.c
)

# target creation
include_directories (${PROJECT_BINARY_DIR} ${GTK2_INCLUDE_DIRS} ${VTE2_INCLUDE_DIRS})
link_directories (${GTK2_LIBRARY_DIRS} ${VTE2_LIBRARY_DIRS})
link_libraries (${GTK2_LIBRARIES} ${VTE2_LIBRARIES})
add_executable (${PROJECT_NAME} ${_SOURCES} ${GTK2_LINK_FLAGS} ${VTE2_LINK_FLAGS})

# install destination
install (TARGETS ${PROJECT_NAME} DESTINATION "bin")
