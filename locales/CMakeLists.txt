# locales/CMakeLists.txt

find_program (LUPDATE_PATH NAMES lupdate-qt4 lupdate)

if (NOT LUPDATE_PATH)
	message (STATUS "lupdate: Not found")
else ()
	message (STATUS "lupdate: ${LUPDATE_PATH}")
	# generate ts file
	add_custom_target (
		create-ts
		COMMAND ${LUPDATE_PATH} ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/data/${PROJECT_NAME}.ui -ts ${PROJECT_SOURCE_DIR}/locales/es_MX.ts
		COMMENT "Generating es_MX ts file"
	)
endif ()
