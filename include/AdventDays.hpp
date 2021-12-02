#pragma once

#include <utility>
#include <vector>
#include <string>
#include <optional>

#include <fmt/core.h>
#include <fmt/color.h>
#include <scn/all.h>

#include "Day01.hpp"
#include "Day02.hpp"

using std::string_literals::operator""s;

const std::string input_directory{"./input/"s};

template <typename D>
concept advent_day = requires {
  typename D::parsed_type;
  typename D::answer_one_type;
  typename D::answer_two_type;
  { D::name() } -> std::same_as<std::string>;
  { D::input_file() } -> std::same_as<std::string>;
  requires requires (char const * cstr) {
    { D::parse(cstr) } -> std::same_as<typename D::parsed_type>;
  };
  requires requires (typename D::parsed_type const& parsed_args, std::optional<typename D::answer_one_type> part1_answer) {
    { D::template solve<false>(parsed_args, part1_answer) } -> std::same_as<typename D::answer_one_type>;
    { D::template solve<true>(parsed_args, part1_answer) } -> std::same_as<typename D::answer_two_type>;
  };
};

template <typename T>
concept scannable = requires (T& t, scn::basic_parse_context<scn::basic_default_locale_ref<char>>& ctx) {
  { t.scan(ctx) } -> std::same_as<scn::error>;
};

template <typename CharT, scannable MyType>
struct scn::scanner<CharT, MyType> : scn::empty_parser {
  template <typename Context>
  error
  scan(MyType& val, Context& ctx) {
    return val.scan(ctx);
  }
};

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

using ALL_ADVENT_DAYS = std::tuple<
  AdventDay<day01::id, day01::parsed, day01::result1, day01::result2>,
  AdventDay<day02::id, day02::parsed, day02::result1, day02::result2>
>;

template <int N>
using get_day = std::tuple_element_t<N - 1, ALL_ADVENT_DAYS>;

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
