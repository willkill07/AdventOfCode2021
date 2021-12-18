add_library(days)

target_include_directories(days
  PUBLIC
  .)

target_sources(days
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
  Day18.cpp)

target_compile_options(days
  PRIVATE
  "-Wconversion"
  "-Wmismatched-dealloc"
  "-Wimplicit-fallthrough=5"
  "-Wdouble-promotion"
  "-Warith-conversion"
  "-Wduplicated-cond"
  "-Wfloat-equal"
  "-Wshadow=local"
  "-Wshadow=global")

target_link_libraries(days PUBLIC advent_common)
