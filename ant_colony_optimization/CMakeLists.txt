cmake_minimum_required( VERSION 3.1)
project(ant_colony_optimization)
include_directories("PROJECT_BINARY_DIR")
add_subdirectory(src)
list(APPEND EXTRA_LIBS src)
list(APPEND EXTRA_INCLUDES "{PROJECT_SOURCE_DIR}/src")
add_executable( main main.cc)
target_link_libraries( main ${EXTRA_LIBS})
target_link_directories(main PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            "${EXTRA_INCLUDES}")