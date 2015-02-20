# src/CMakeLists.txt

set (GTKMM2_VERSION_NEED "2.20")
set (VTEMM2_VERSION_NEED "0.25")

# set link flags
set (LINKER_FLAGS)

# sources
set (_SOURCES FormUI.cpp main.cpp)

# search for pkg-config
include (FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
	message (FATAL_ERROR "pkg-config not found")
endif ()

# check for gtkmm-2.4
pkg_check_modules (GTKMM2 gtkmm-2.4>=${GTKMM2_VERSION_NEED} REQUIRED)
if (NOT GTKMM2_FOUND)
	message(FATAL_ERROR "You don't seem to have gtkmm-2.4 development libraries version ${GTKMM2_VERSION_NEED} or better installed")
else ()
	include_directories (${GTKMM2_INCLUDE_DIRS})
	link_directories (${GTKMM2_LIBRARY_DIRS})
	set (LINKER_FLAGS ${LINKER_FLAGS} ${GTKMM2_LINK_FLAGS})
endif ()

# check for libvtemm
pkg_check_modules (VTEMM libvtemm-1.2>=${VTEMM2_VERSION_NEED} REQUIRED)
if (NOT VTEMM_FOUND)
	message(FATAL_ERROR "You don't seem to have gtkmm-2.4 development libraries version ${GTKMM2_VERSION_NEED} or better installed")
else ()
	include_directories (${VTEMM_INCLUDE_DIRS})
	link_directories (${VTEMM_LIBRARY_DIRS})
	set (LINKER_FLAGS ${LINKER_FLAGS} ${VTEMM_LINK_FLAGS})
endif ()

# target creation
add_executable (${PROJECT_NAME} ${_SOURCES} ${LINKER_FLAGS})
target_link_libraries (${PROJECT_NAME} ${GTKMM2_LIBRARIES} ${VTEMM_LIBRARIES})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# install destination
install (TARGETS ${PROJECT_NAME} DESTINATION "bin")
