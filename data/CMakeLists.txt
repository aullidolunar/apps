# data/CMakeLists.txt

# desktop file
set (_DESKTOP_FILE_IN "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.desktop.in")
if (EXISTS "${_DESKTOP_FILE_IN}" AND UNIX)
	set (_DESKTOP_FILE "${PROJECT_BINARY_DIR}/data/${PROJECT_NAME}.desktop")
	configure_file ("${_DESKTOP_FILE_IN}" "${_DESKTOP_FILE}")
	install (FILES "${_DESKTOP_FILE}" DESTINATION "share/applications")
endif ()
