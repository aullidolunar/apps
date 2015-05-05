# data/CMakeLists.txt

# it is best only to generate .desktop.in here (go to po/CMakeLists.txt for extracting translation strings)
if (EXISTS "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.desktop.in.in" AND UNIX)
	configure_file (
		"${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.desktop.in.in"
		"${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop.in"
	)
endif ()

file (GLOB DATA_FILES *.*)
foreach (DATA_FILE ${DATA_FILES})
	get_filename_component (FILE_EXT ${DATA_FILE} EXT)
	if ((${FILE_EXT} MATCHES ".txt") OR (${FILE_EXT} MATCHES ".desktop.in.in") OR (${FILE_EXT} MATCHES ".rc.in") OR (${FILE_EXT} MATCHES ".h"))
	else ()
		install (FILES "${DATA_FILE}" DESTINATION "${_PROJECT_INSTALL_DIR}")
	endif()
endforeach ()
