add_library(days)

target_sources(days
  PRIVATE
  Day01.cpp)

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