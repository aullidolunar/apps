cmake_minimum_required (VERSION 3.1)

# cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_CXX_FLAGS_RELEASE:STRING="/MT" -DCMAKE_BUILD_TYPE=Debug ..
# cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug ..

set (_PROGRAM_ "Alarm")
set (_VERSION_ "2.0.0.0")

project (${_PROGRAM_} VERSION ${_VERSION_} LANGUAGES CXX)

# test build type
if (CMAKE_BUILD_TYPE STREQUAL "")
	set (CMAKE_BUILD_TYPE "Debug")
	add_definitions (-DDEBUG -D_DEBUG)
else ()
	add_definitions (-DNDEBUG -D_NDEBUG)
endif ()

# source files
list (APPEND SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/form.cxx" "${PROJECT_SOURCE_DIR}/src/main.cxx")

# header files
set (HEADER_FILES "${PROJECT_SOURCE_DIR}/src/form.hxx")

# qt resource file
set (RES_FILE "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.qrc")

# ui file
set (UI_FILE "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.ui")

# translations resource file
set (TRANS_FILE "${PROJECT_SOURCE_DIR}/translations/translations.qrc")

# This can be done with qt4 or qt5
option (USE_QT4 "Build with qt4 support" ON)
if (${USE_QT4})
	# find Qt4 >= 4.6
	find_package (Qt4 4.6 REQUIRED QtCore QtGui)
	if (NOT Qt4_FOUND)
		message (FATAL_ERROR "Error finding qt4")
	else ()
		# set Qt version to use
		set (QT_VERSION 4)
		# we need phonon
		find_package(Phonon REQUIRED)
		include_directories ("${PHONON_INCLUDE_DIR}")
		if (UNIX)
			# hack for archlinux path
			include_directories ("/usr/include/qt4/KDE")
		endif ()
		# Qt4 macros
		qt4_wrap_cpp (QT_MOC_FILE ${HEADER_FILES})
		qt4_wrap_ui (QT_UI_FILE ${UI_FILE})
		qt4_add_resources (QT_RES_FILE ${RES_FILE})
		# pass libs
		list (APPEND QT_LIBS Qt4::QtCore Qt4::QtGui ${PHONON_LIBRARY})
		# pack the tools
		set (LRELEASE_EXECUTABLE ${QT_LRELEASE_EXECUTABLE})
		set (RCC_EXECUTABLE ${QT_RCC_EXECUTABLE})
	endif ()
	# create proper binary name
	set (BIN_QT_NAME "${PROJECT_NAME}Qt4")
else ()
	# find Qt5
	find_package (Qt5Widgets REQUIRED)
	if (NOT Qt5Widgets_FOUND)
		message (FATAL_ERROR "Error finding qt5")
	else ()
		# check for Qt5LinguistTools (lrelease, lupdate, ...)
		find_package (Qt5LinguistTools REQUIRED)
		# set Qt version to use
		set (QT_VERSION 5)
		# add qt5 modules to include path
		include_directories ("${Qt5Widgets_INCLUDE_DIRS}")
		# we need to phonon
		find_package (Phonon4Qt5 REQUIRED)
		include_directories ("${PHONON_INCLUDE_DIR}")
		if (UNIX)
			# hack for archlinux path
			include_directories ("/usr/include/phonon4qt5/KDE")
		endif ()
		# Qt5 macros
		qt5_wrap_cpp (QT_MOC_FILE ${HEADER_FILES})
		qt5_wrap_ui (QT_UI_FILE ${UI_FILE})
		qt5_add_resources (QT_RES_FILE ${RES_FILE})
		# pass libs
		list (APPEND QT_LIBS ${Qt5Widgets_LIBRARIES} ${PHONON_LIBRARY})
		# pack the tools
		set (LRELEASE_EXECUTABLE ${Qt5_LRELEASE_EXECUTABLE})
		set (RCC_EXECUTABLE ${Qt5Core_RCC_EXECUTABLE})
	endif ()
	# create proper binary name
	set (BIN_QT_NAME "${PROJECT_NAME}Qt${QT_VERSION}")
endif ()

configure_file (
	"${PROJECT_SOURCE_DIR}/src/config.h.in" 
	"${PROJECT_BINARY_DIR}/config.h"
)
add_definitions (-DHAVE_CONFIG_H)

# append source files
list (APPEND SOURCE_FILES ${QT_MOC_FILE} ${QT_UI_FILE} ${QT_RES_FILE})

# grab ts files from translations directory
file (GLOB TS_FILES "${PROJECT_SOURCE_DIR}/translations/*.ts")
# tell me if we have ts files
list (LENGTH TS_FILES TS_FILES_LEN)
if (TS_FILES_LEN GREATER 0)
	# since we have files...
	foreach (TS_FILE ${TS_FILES})
		get_filename_component (QM_FILENAME ${TS_FILE} NAME_WE)
		add_custom_command (
			OUTPUT ${PROJECT_BINARY_DIR}/${QM_FILENAME}.qm
			COMMAND ${LRELEASE_EXECUTABLE} ${TS_FILE} -qm ${PROJECT_BINARY_DIR}/${QM_FILENAME}.qm
			COMMENT "Processing ${QM_FILENAME}.ts"
			DEPENDS ${TS_FILE}
		)
		list (APPEND QM_FILES ${PROJECT_BINARY_DIR}/${QM_FILENAME}.qm)
	endforeach ()
	# generate translations qrc
	set (QRC_TRANS "${PROJECT_BINARY_DIR}/qrc_translations.cpp")
	add_custom_command (
		OUTPUT ${QRC_TRANS}
		WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
		DEPENDS ${QM_FILES}
		COMMAND ${CMAKE_COMMAND} -E copy "${TRANS_FILE}" "${PROJECT_BINARY_DIR}"
		COMMAND ${RCC_EXECUTABLE} -o "qrc_translations.cpp" "translations.qrc"
		COMMENT "Generating qrc for translations"
	)
	# append source files
	list (APPEND SOURCE_FILES ${QRC_TRANS})
endif ()

include_directories (${PROJECT_BINARY_DIR})
add_executable (${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries (${PROJECT_NAME} ${QT_LIBS})
set_target_properties (${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${BIN_QT_NAME})
set_directory_properties (PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "config.h;CMakeCache.txt;cmake_install.cmake")

add_custom_target ("run"
	COMMAND ${PROJECT_BINARY_DIR}/${BIN_QT_NAME}
	DEPENDS ${PROJECT_NAME}
)

add_custom_target (
	create-ts
	COMMAND ${QT_LUPDATE_EXECUTABLE} -noobsolete ${PROJECT_SOURCE_DIR}/src/form.cxx ${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.ui -ts ${PROJECT_SOURCE_DIR}/translations/es.ts
	COMMENT "Generating ts file"
)

message (STATUS "Looking for tar binary")
find_program (TAR_PATH tar)
if (TAR_PATH)
	message (STATUS "-- tar found.")
	add_custom_target ("dist"
		WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
		COMMAND ${CMAKE_COMMAND} -E copy_directory ../data ${PROJECT_NAME}-${PROJECT_VERSION}/data
		COMMAND ${CMAKE_COMMAND} -E copy_directory ../translations ${PROJECT_NAME}-${PROJECT_VERSION}/translations
		COMMAND ${CMAKE_COMMAND} -E copy_directory ../src ${PROJECT_NAME}-${PROJECT_VERSION}/src
		COMMAND ${CMAKE_COMMAND} -E copy ../CMakeLists.txt ${PROJECT_NAME}-${PROJECT_VERSION}
		COMMAND ${TAR_PATH} -cvzf ../${PROJECT_NAME}-${PROJECT_VERSION}.tar.gz ${PROJECT_NAME}-${PROJECT_VERSION}
		COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_NAME}-${PROJECT_VERSION}
		COMMENT "Generating tarball source code"
	)
else ()
	message (STATUS "-- tar not found.")
endif ()

# EOF :~
