cmake_minimum_required(VERSION 3.18)
project(AdventOfCode2020 CXX)

add_subdirectory(fmt)
add_subdirectory(scnlib)
add_subdirectory(argparse)

add_library(advent_common INTERFACE)
target_compile_features(advent_common INTERFACE cxx_std_20)
target_include_directories(advent_common INTERFACE "include")
target_compile_options(advent_common INTERFACE "-Wall" "-Wextra" "-Wpedantic" "-Os")
target_link_libraries(advent_common INTERFACE fmt::fmt scn::scn)

add_subdirectory(days)

add_executable(advent)
target_sources(advent PRIVATE Advent.cpp)
target_link_libraries(advent PUBLIC argparse::argparse advent_common days)
