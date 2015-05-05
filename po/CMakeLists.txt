# po/CMakeLists.txt

# enable this only in maintainer mode to generate es.po file
if (${ENABLE_MAINTAINER})
	find_program (XGETTEXT xgettext)
	if (NOT XGETTEXT)
		message (FATAL_ERROR "xgettext not found")
	else ()
		message (STATUS "xgettext: ${XGETTEXT}")
	endif ()
	find_program(MSGFMT msgfmt)
	if (NOT MSGFMT)
		message (FATAL_ERROR "msgfmt not found")
	else ()
		message (STATUS "msgfmt: ${MSGFMT}")
	endif ()
	find_program(MSGINIT msginit)
	if (NOT MSGINIT)
		message (FATAL_ERROR "msginit not found")
	else ()
		message (STATUS "msginit: ${MSGINIT}")
	endif ()
	find_program(MSGMERGE msgmerge)
	if (NOT MSGMERGE)
		message (FATAL_ERROR "msgmerge not found")
	else ()
		message (STATUS "msgmerge: ${MSGMERGE}")
	endif ()
	find_program(INTLTOOLEXTRACT intltool-extract)
	if (NOT INTLTOOLEXTRACT)
		message (WARNING "intltool-extract not found")
	else ()
		message (STATUS "intltool-extract: ${INTLTOOLEXTRACT}")
	endif ()
	find_program(INTLTOOLMERGE intltool-merge)
	if (NOT INTLTOOLMERGE)
		message (FATAL_ERROR "intltool-merge not found")
	else ()
		message (STATUS "intltool-merge: ${INTLTOOLMERGE}")
	endif ()
	# desktop file: extract strings before running create-es target
	if (EXISTS "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop.in")
		add_custom_command (
			OUTPUT "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop.in.h"
			WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
			COMMAND ${INTLTOOLEXTRACT} --type="gettext/ini" "${PROJECT_NAME}.desktop.in"
			COMMENT "Extracting desktop file translation strings"
		)
	endif ()
	# builder file: extract strings before running create-es target
	if (EXISTS "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.builder")
		add_custom_command (
			OUTPUT "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.builder.h"
			WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/data"
			COMMAND ${INTLTOOLEXTRACT} --type="gettext/glade" "${PROJECT_NAME}.builder"
			COMMAND ${CMAKE_COMMAND} -E rename "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.builder.h" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.builder.h"
			COMMENT "Extracting builder file translation strings"
		)
	endif ()
	add_custom_command(
		OUTPUT "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pot"
		DEPENDS "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop.in.h" "${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.builder.h"
		COMMAND ${XGETTEXT} -o "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pot" --no-wrap --copyright-holder=${EMAIL} --package-name=${PROJECT_NAME} --package-version=${PROJECT_VERSION} --msgid-bugs-address=${EMAIL} --keyword=_ --keyword=N_ --from-code=utf-8 ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_BINARY_DIR}/*.h
		COMMENT "Generating pot file"
	)
	add_custom_target (create-es
		DEPENDS "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pot"
		COMMAND ${MSGINIT} --no-translator --no-wrap -i "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pot" -o "${PROJECT_SOURCE_DIR}/po/es.po" -l es_MX.utf8
		COMMENT "Generating spanish po file"
	)
	add_custom_target(update-es
		DEPENDS "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pot"
		COMMAND ${MSGMERGE} --update -N --no-wrap "${PROJECT_SOURCE_DIR}/po/es.po" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pot"
		COMMAND ${CMAKE_COMMAND} -E remove "${PROJECT_SOURCE_DIR}/po/es.po~"
		COMMENT "Updating spanish po file"
	)
endif ()

# only generate these targets if we actually have po files
file (GLOB PO_FILES "${PROJECT_SOURCE_DIR}/po/*.po")
list (LENGTH PO_FILES PO_FILES_LEN)
if (PO_FILES_LEN GREATER 0)
	if ((EXISTS "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop.in") AND UNIX)
		add_custom_command(
			OUTPUT "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop"
			WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
			COMMAND ${INTLTOOLMERGE} -d -u "../po" "${PROJECT_NAME}.desktop.in" "${PROJECT_NAME}.desktop"
			COMMENT "Creating desktop file"
		)
		add_custom_target (desktopfile DEPENDS "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop")
		add_dependencies (${PROJECT_NAME} desktopfile)
		install (FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.desktop" DESTINATION "share/applications")
	endif ()
	foreach(_poFile ${PO_FILES})
		get_filename_component(_lang ${_poFile} NAME_WE)
		if (NOT EXISTS "${PROJECT_BINARY_DIR}/locale/${_lang}/LC_MESSAGES/")
			add_custom_command (
				OUTPUT "${PROJECT_BINARY_DIR}/locale/${_lang}/LC_MESSAGES/"
				COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/locale/${_lang}/LC_MESSAGES/"
				COMMENT "Reading locale ${_lang}"
			)
			# set (LOCALE_DIRS ${LOCALE_DIRS} "${PROJECT_BINARY_DIR}/locale/${_lang}/LC_MESSAGES/")
		endif ()
		add_custom_command(
			OUTPUT "${PROJECT_BINARY_DIR}/locale/${_lang}/LC_MESSAGES/${PROJECT_NAME}.mo"
			DEPENDS "${PROJECT_BINARY_DIR}/locale/${_lang}/LC_MESSAGES/"
			COMMAND ${MSGFMT} ${_poFile} -o "${PROJECT_BINARY_DIR}/locale/${_lang}/LC_MESSAGES/${PROJECT_NAME}.mo"
			COMMENT "Building ${_lang} translation"
		)
		set (MO_FILES ${MO_FILES} "${PROJECT_BINARY_DIR}/locale/${_lang}/LC_MESSAGES/${PROJECT_NAME}.mo")
		install (FILES "${PROJECT_BINARY_DIR}/locale/${_lang}/LC_MESSAGES/${PROJECT_NAME}.mo" DESTINATION "${LOCALE_PREFIX}/${_lang}/LC_MESSAGES")
	endforeach(_poFile ${PO_FILES})
	add_custom_target (locales DEPENDS ${MO_FILES})
	add_dependencies (${PROJECT_NAME} locales)
endif ()
