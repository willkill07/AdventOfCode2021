#pragma once

#include <utility>
#include <vector>
#include <string>
#include <optional>

#include <fmt/core.h>
#include <fmt/color.h>

using std::string_literals::operator""s;

const std::string input_directory{"./input/"s};

template <int Day, typename ParsedT, typename ResultOneT, typename ResultTwoT = ResultOneT>
struct AdventDay {

  using parsed_type = ParsedT;
  using answer_one_type = ResultOneT;
  using answer_two_type = ResultTwoT;

  inline static std::string name() {
    return fmt::format("Day {:02}:", Day);
  }

  inline static std::string input_file() {
    return fmt::format("{}/day{:02}.txt", input_directory, Day);
  }

  static
  parsed_type
  parse(char const*);

  template <bool solve_part2>
  static
  std::conditional_t<solve_part2, answer_two_type, answer_one_type>
  solve(parsed_type const&, std::optional<answer_one_type> = std::nullopt);
};

#define INSTANTIATE(DAY,BOOL) \
template \
std::conditional_t< \
  BOOL, \
  typename DAY::answer_two_type, \
  typename DAY::answer_one_type \
> \
DAY::solve<BOOL>( \
  typename DAY::parsed_type const&, \
  std::optional<typename DAY::answer_one_type> \
)
