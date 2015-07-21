# data/CMakeLists.txt

# desktop file
set (_DESKTOP_FILE_IN "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.desktop.in")
if (EXISTS "${_DESKTOP_FILE_IN}" AND UNIX)
	set (_DESKTOP_FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop")
	configure_file ("${_DESKTOP_FILE_IN}" "${_DESKTOP_FILE}")
	install (FILES "${_DESKTOP_FILE}" DESTINATION "share/applications")
	install (FILES "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.png" DESTINATION "share/${PROJECT_NAME}")
endif ()

# Generate proper resource file output
set (RESOURCE_FILE_IN "${PROJECT_SOURCE_DIR}/data/resource.rc.in")
if (EXISTS "${RESOURCE_FILE_IN}" AND WIN32)
	if (MSVC)
		find_program(RC_PATH rc)
		set (RESOURCE_OBJECT "${PROJECT_BINARY_DIR}/resource.res")
	else ()
		find_program(RC_PATH windres)
		set (RESOURCE_OBJECT "${PROJECT_BINARY_DIR}/resource.o")
	endif ()
	if (NOT RC_PATH)
		message (FATAL_ERROR "Resource compiler not found (required)")
	else ()
		message (STATUS "RC: ${RC_PATH}")
		set (RESOURCE_FILE_OUT "${PROJECT_BINARY_DIR}/resource.rc")
		configure_file ("${RESOURCE_FILE_IN}" "${RESOURCE_FILE_OUT}")
		if (MSVC)
			set (RC_CMD ${RC_PATH} ${RESOURCE_FILE_OUT})
		else ()
			set (RC_CMD ${RC_PATH} ${RESOURCE_FILE_OUT} -o ${RESOURCE_OBJECT})
		endif ()
		set (RESOURCE_FILE_OUT ${RESOURCE_FILE_OUT} PARENT_SCOPE)
		set (RESOURCE_OBJECT ${RESOURCE_OBJECT} PARENT_SCOPE)
		set (RC_CMD ${RC_CMD} PARENT_SCOPE)
		message (STATUS "Resource output: ${RESOURCE_FILE_OUT}")
	endif ()
endif ()

install (FILES "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.ogg" DESTINATION "share/${PROJECT_NAME}")

# EOF: ~
