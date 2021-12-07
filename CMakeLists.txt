cmake_minimum_required(VERSION 3.18)
project(AdventOfCode2020 CXX)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        origin/master
)
FetchContent_Declare(
  scnlib
  GIT_REPOSITORY https://github.com/eliaskosunen/scnlib.git
  GIT_TAG        origin/master
)
FetchContent_Declare(
  argparse
  GIT_REPOSITORY https://github.com/p-ranav/argparse.git
  GIT_TAG        origin/master
)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        origin/devel
)
FetchContent_MakeAvailable(fmt scnlib argparse catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(CTest)
include(Catch)

add_custom_target(copy-input ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/input
  ${CMAKE_BINARY_DIR}/input)

add_library(advent_common INTERFACE)
target_compile_features(advent_common INTERFACE cxx_std_20)
target_include_directories(advent_common INTERFACE "include")
target_compile_options(advent_common INTERFACE "-Wall" "-Wextra" "-Wpedantic")
target_link_libraries(advent_common INTERFACE fmt::fmt scn::scn)

add_subdirectory(days)

add_subdirectory(tests)

add_subdirectory(src)
