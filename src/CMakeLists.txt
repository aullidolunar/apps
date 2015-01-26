# src/CMakeLists.txt

message (STATUS "+- entering SRC directory -+")

# target creation
add_executable (${PROJECT_NAME} ${_SOURCES} ${LINKER_FLAGS})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# install destination
install (TARGETS ${PROJECT_NAME} DESTINATION "bin")
