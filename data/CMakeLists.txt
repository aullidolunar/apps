# data/CMakeLists.txt

# desktop file
set (_DESKTOP_FILE_IN_IN "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.desktop.in.in")

if (EXISTS ${_DESKTOP_FILE_IN_IN})
	find_program(INTLTOOLMERGE intltool-merge)
	
	if (NOT INTLTOOLMERGE)
		message (FATAL_ERROR "intltool-merge not found (required)")
	endif ()
	
	set (_DESKTOP_FILE_IN "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop.in")
	configure_file ("${_DESKTOP_FILE_IN_IN}" "${_DESKTOP_FILE_IN}")
	set (_DESKTOP_FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop")
	add_custom_command(
		OUTPUT "${_DESKTOP_FILE}"
		COMMAND ${INTLTOOLMERGE} -d -u ../../po "${_DESKTOP_FILE_IN}" "${_DESKTOP_FILE}"
		COMMENT "Creating desktop file"
	)
	set (_DESKTOP_FILE_IN "${_DESKTOP_FILE_IN}" PARENT_SCOPE)
	install (FILES "${_DESKTOP_FILE}" DESTINATION "share/applications")
	add_custom_target (desktopfile DEPENDS ${_DESKTOP_FILE})
	add_dependencies (${PROJECT_NAME} desktopfile)
	
endif ()

# builder file
set (_UI_FILE "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.builder")
if (EXISTS "${_UI_FILE}")
	set (_UI_FILE "${_UI_FILE}" PARENT_SCOPE)
endif ()

file (GLOB DATA_FILES *.*)
foreach (DATA_FILE ${DATA_FILES})
	get_filename_component (FILE_EXT ${DATA_FILE} EXT)
	if ((${FILE_EXT} MATCHES ".txt") OR (${FILE_EXT} MATCHES ".desktop.in.in"))
	else ()
		install (FILES "${DATA_FILE}" DESTINATION "share/${PROJECT_NAME}")
	endif()
endforeach ()
