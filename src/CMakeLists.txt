# src/CMakeLists.txt

# sources
set (_SOURCES reguser.cpp main.cpp)

# headers
set (_HEADERS reguser.hpp)

find_package (Qt4 4.6 REQUIRED)
include (${QT_USE_FILE})

# qt-ish stuff (don't remove)
set (OTHER_QT_SOURCES)

qt4_wrap_cpp (_MOC ${_HEADERS})

if (EXISTS "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.ui")
	qt4_wrap_ui (_UIFILE "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.ui")
	set (OTHER_QT_SOURCES "${OTHER_QT_SOURCES}" ${_UIFILE})
endif ()

if (EXISTS "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.qrc")
	qt4_add_resources (_RESOURCE "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.qrc")
	set (OTHER_QT_SOURCES "${OTHER_QT_SOURCES}" ${_RESOURCE})
endif ()

# do resource
if (EXISTS "${PROJECT_SOURCE_DIR}/src/resource.rc.in" AND WIN32)
	find_program(RC_PATH RC)
	if (NOT RC_PATH)
		message (FATAL_ERROR "RC not found (required)")
	endif ()
	set (RESOURCE_FILE_IN "${PROJECT_SOURCE_DIR}/src/resource.rc.in")
	set (RESOURCE_FILE_OUT "${PROJECT_BINARY_DIR}/resource.rc")
	set (RESOURCE_OBJECT "${PROJECT_BINARY_DIR}/resource.RES")
	configure_file ("${RESOURCE_FILE_IN}" "${RESOURCE_FILE_OUT}")
	add_custom_command (
		OUTPUT "${RESOURCE_OBJECT}"
		COMMAND ${RC_PATH} /i ${PROJECT_SOURCE_DIR}/src /i ${PROJECT_BINARY_DIR} "${RESOURCE_FILE_OUT}"
		COMMENT "Compiling resource file"
	)
	add_custom_target (resourcefile DEPENDS ${RESOURCE_OBJECT})
	# yes, you need the next line, don't forget it
	set_source_files_properties (${RESOURCE_OBJECT} PROPERTIES EXTERNAL_OBJECT true GENERATED true)
	set (_SOURCES ${_SOURCES} ${RESOURCE_OBJECT})
endif ()

# target creation
add_executable (${PROJECT_NAME} ${_MOC} ${_SOURCES} ${OTHER_QT_SOURCES})
target_link_libraries (${PROJECT_NAME} ${QT_QTMAIN_LIBRARY} ${QT_LIBRARIES})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# install destination
install (TARGETS ${PROJECT_NAME} DESTINATION "${_PROJECT_INSTALL_DIR}")

# get translation files
file (GLOB TRANSLATIONS ${PROJECT_SOURCE_DIR}/locales/*.ts)
list (LENGTH TRANSLATIONS TRANSLATIONS_FILES_LEN)
if (TRANSLATIONS_FILES_LEN GREATER 0)
	find_program (LRELEASE_PATH NAMES lrelease-qt4 lrelease)
	if (NOT LRELEASE_PATH)
		message (FATAL_ERROR "lrelease: Not found")
	else ()
		message (STATUS "lrelease: ${LRELEASE_PATH}")
		if (WIN32)
			set (QM_PATH "${PROJECT_NAME}/locales")
		else ()
			set (QM_PATH "share/${PROJECT_NAME}/locales")
		endif ()
		foreach (TS_FILE ${TRANSLATIONS})
			get_filename_component(_ts_file ${TS_FILE} NAME_WE)
			set (QM_FILE ${PROJECT_BINARY_DIR}/locales/${_ts_file}.qm)
			add_custom_command(
				TARGET ${PROJECT_NAME}
				COMMAND ${LRELEASE_PATH} ${TS_FILE} -qm ${QM_FILE}
				COMMENT "Generating ${_ts_file}.qm file"
			)
			install (FILES ${QM_FILE} DESTINATION ${QM_PATH})
		endforeach ()
	endif ()
endif ()

