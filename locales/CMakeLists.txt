# locales/CMakeLists.txt

# generate ts file
add_custom_target (
	create-ts
	COMMAND ${QT_LUPDATE_EXECUTABLE} ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/data/*.ui -ts ${PROJECT_SOURCE_DIR}/locales/es_MX.ts
	COMMENT "Generating es_MX ts file"
)

# EOF: ~
