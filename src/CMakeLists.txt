add_executable(advent)
target_sources(advent PRIVATE Advent.cpp)
target_link_libraries(advent PUBLIC argparse::argparse advent_common days)

set_target_properties(advent PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

add_dependencies(advent copy-input)