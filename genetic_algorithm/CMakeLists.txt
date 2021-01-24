cmake_minimum_required(VERSION 3.1)
project( genetic_algorithm )
add_subdirectory(src)
list(APPEND EXTRA_DIRS src)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/src")
add_executable( main main.cc )
target_link_libraries( main ${EXTRA_DIRS})
target_include_directories( main PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            "${EXTRA_INCLUDES}")