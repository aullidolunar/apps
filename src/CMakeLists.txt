# src/CMakeLists.txt

# sources
set (_SOURCES pref.cc alarm.cc main.cc)

# headers
set (_HEADERS alarm.hh pref.hh)

# qt-ish stuff (don't remove)
set (OTHER_QT_SOURCES)

qt4_wrap_cpp (_MOC ${_HEADERS})

if (EXISTS "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.ui")
	list (APPEND QT_UI_FILES "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.ui")
endif ()

if (EXISTS "${PROJECT_SOURCE_DIR}/data/pref.ui")
	list (APPEND QT_UI_FILES "${PROJECT_SOURCE_DIR}/data/pref.ui")
endif ()

qt4_wrap_ui (_UIFILES ${QT_UI_FILES})
set (OTHER_QT_SOURCES "${OTHER_QT_SOURCES}" ${_UIFILES})

# tell cmake create a resource file with translations
# see: http://stackoverflow.com/questions/3125327/how-to-integrate-qt4-qm-files-into-binary-using-cmake-and-qrc
# Grab ts files
file (GLOB TS_FILES "${PROJECT_SOURCE_DIR}/locales/*.ts")
# How many are they?
list (LENGTH TS_FILES TS_FILES_LEN)
# be sure is > 0
if (TS_FILES_LEN GREATER 0)
	# qt4_add_translation (QM_FILES ${TS_FILES})
	# set here the translation name file
	set (LOCALE_QRC "${PROJECT_BINARY_DIR}/locale.qrc")
	file (WRITE ${LOCALE_QRC} "<RCC>\n\t<qresource prefix=\"locales\">")
	# write each file name to the locale resource
	foreach(TS_FILE ${TS_FILES})
		get_filename_component(TS_FILE_NAME ${TS_FILE} NAME_WE)
		file(APPEND ${LOCALE_QRC} "\n\t\t<file alias=\"${TS_FILE_NAME}\">locales/${TS_FILE_NAME}.qm</file>")
		add_custom_command (
			OUTPUT "${PROJECT_BINARY_DIR}/locales/${TS_FILE_NAME}.qm"
			COMMAND ${QT_LRELEASE_EXECUTABLE} ${TS_FILE} -qm "${PROJECT_BINARY_DIR}/locales/${TS_FILE_NAME}.qm"
			COMMENT "Generating ${TS_FILE_NAME}.qm file"
			DEPENDS ${TS_FILE}
		)
	endforeach()
	file (APPEND ${LOCALE_QRC} "\n\t</qresource>\n</RCC>")
	list (APPEND QT_RESOURCE_FILES ${LOCALE_QRC})
endif ()

if (EXISTS "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.qrc")
	list (APPEND QT_RESOURCE_FILES "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.qrc")
endif ()

qt4_add_resources (_RESOURCE "${QT_RESOURCE_FILES}")
set (OTHER_QT_SOURCES "${OTHER_QT_SOURCES}" ${_RESOURCE})

# do win32 resource
if (EXISTS "${RESOURCE_FILE_OUT}")
	add_custom_command (
		OUTPUT "${RESOURCE_OBJECT}"
		COMMAND ${RC_CMD}
		COMMENT "Compiling resource file"
	)
	add_custom_target (resourcefile DEPENDS ${RESOURCE_OBJECT})
	set_source_files_properties (${RESOURCE_OBJECT} PROPERTIES EXTERNAL_OBJECT true GENERATED true)
	set (_SOURCES ${_SOURCES} ${RESOURCE_OBJECT})
endif ()

# this one is for phonon on linux, at least in archlinux
if (UNIX)
	include_directories ("/usr/include/qt4/KDE")
endif ()

# target creation
add_executable (${PROJECT_NAME} ${_MOC} ${_SOURCES} ${OTHER_QT_SOURCES})
target_link_libraries (${PROJECT_NAME} ${QT_QTMAIN_LIBRARY} ${QT_LIBRARIES})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# install destination
install (TARGETS ${PROJECT_NAME} DESTINATION "${_PROJECT_INSTALL_DIR}")

# EOF: ~
