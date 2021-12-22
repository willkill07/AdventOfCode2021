add_executable(advent_tests)
target_link_libraries(advent_tests
  PRIVATE
  days
  Catch2::Catch2WithMain)

target_sources(advent_tests
  PRIVATE
  Day01.cpp
  Day02.cpp
  Day03.cpp
  Day04.cpp
  Day05.cpp
  Day06.cpp
  Day07.cpp
  Day08.cpp
  Day09.cpp
  Day10.cpp
  Day11.cpp
  Day12.cpp
  Day13.cpp
  Day14.cpp
  Day15.cpp
  Day16.cpp
  Day17.cpp
  Day18.cpp
  Day19.cpp
  Day20.cpp
  Day21.cpp
  AdventTest.cpp)

set_target_properties(advent_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

catch_discover_tests(advent_tests EXTRA_ARGS -s)