add_executable(tests)
target_link_libraries(tests
  PUBLIC
  days
  Catch2::Catch2WithMain)

target_sources(tests
  PUBLIC
  Day01.cpp
  Day02.cpp)

catch_discover_tests(tests EXTRA_ARGS -s)