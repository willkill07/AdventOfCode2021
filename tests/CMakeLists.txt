add_executable(tests)
target_link_libraries(tests
  PRIVATE
  days
  Catch2::Catch2WithMain)

target_sources(tests
  PRIVATE
  Day01.cpp
  Day02.cpp
  Day03.cpp
  Day04.cpp
  Day05.cpp
  Day06.cpp
  AdventTest.cpp)

catch_discover_tests(tests EXTRA_ARGS -s)