#pragma once

#include <utility>
#include <vector>
#include <string>
#include <string_view>
#include <optional>

#include <fmt/core.h>
#include <fmt/color.h>

using std::string_literals::operator""s;

const std::string input_directory{"./input/"s};

template <int Day, typename ParsedT, typename ResultOneT, typename ResultTwoT>
struct AdventDay {
  
  using parsed_type = ParsedT;
  using part1_answer = ResultOneT;
  using part2_answer = ResultTwoT;
  using opt_answer = std::optional<ResultOneT>;

  template <bool solve_part2>
  using answer = std::conditional_t<solve_part2, ResultTwoT, ResultOneT>;

  inline static std::string name() {
    return fmt::format("Day {:02}:", Day);
  }

  inline static std::string input_file() {
    return fmt::format("{}/day{:02}.txt", input_directory, Day);
  }

  static
  parsed_type
  parse(std::string const&);

  template <bool solve_part2>
  static
  answer<solve_part2>
  solve(parsed_type const&, opt_answer = std::nullopt);
};

#define INSTANTIATE(DAY,BOOL) \
template \
DAY::answer<BOOL> \
DAY::solve<BOOL>( \
  DAY::parsed_type const&, \
  DAY::opt_answer \
)
