# data/CMakeLists.txt

find_program(INTLTOOLMERGE intltool-merge)
if (NOT INTLTOOLMERGE)
	message (FATAL_ERROR "intltool-merge not found (required)")
endif (NOT INTLTOOLMERGE)

configure_file (
	"${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.desktop.in.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop.in"
)

set (DESKTOP_FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop")
add_custom_command(
	OUTPUT "${DESKTOP_FILE}"
	COMMAND ${INTLTOOLMERGE} -d -u ../../po ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop.in ${DESKTOP_FILE}
	COMMENT "Creating desktop file"
)

add_custom_target (desktopfile DEPENDS ${DESKTOP_FILE})
add_dependencies (${PROJECT_NAME} desktopfile)

install (FILES "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.builder" DESTINATION "share/${PROJECT_NAME}")
install (FILES "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.png" DESTINATION "share/${PROJECT_NAME}")
install (FILES "${PROJECT_SOURCE_DIR}/data/download.png" DESTINATION "share/${PROJECT_NAME}")
install (FILES "${PROJECT_SOURCE_DIR}/data/error.png" DESTINATION "share/${PROJECT_NAME}")
install (FILES "${PROJECT_SOURCE_DIR}/data/wait.png" DESTINATION "share/${PROJECT_NAME}")
install (FILES "${DESKTOP_FILE}" DESTINATION "share/applications")
