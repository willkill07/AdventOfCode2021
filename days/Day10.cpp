#include <algorithm>
#include <bitset>
#include <cctype>
#include <limits>
#include <memory>
#include <numeric>
#include <ranges>
#include <vector>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day10.hpp"

namespace detail {
  using namespace day10;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  Day::parsed_type result;
  result.reserve(150);
  auto const end = file.end();
  for (auto iter = file.begin(); iter < end; ) {
    auto end_of_line = std::find(iter, end, '\n');
    result.emplace_back(iter, end_of_line);
    iter = end_of_line + 1;
  }
  return result;
}

auto const matches = detail::matches();
auto const scores = detail::scores();
auto const illegal_values = detail::illegal_values();

inline bool
opening(char a) {
  return a == '{' or a == '(' or a == '[' or a == '<';
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  std::vector<char> stack;
  stack.reserve(128);
  std::conditional_t<solve_part2, std::vector<unsigned long>, unsigned long> result{};
  if constexpr (solve_part2) {
    result.reserve(data.size());
  }
  for (auto&& line : data) {
    for (auto c : line) {
      if (opening(c)) {
        stack.push_back(c);
      } else {
        auto const top = stack.back();
        stack.pop_back();
        if (matches[c >> 4] != top) {
          if constexpr (not solve_part2) {
            result += illegal_values[c >> 4];
          }
          stack.clear();
          break;
        }
      }
    }
    if constexpr (solve_part2) {
      if (not stack.empty()) {
        unsigned long sum{0};
        for (char c : stack | std::views::reverse) {
          sum = 5 * sum + scores[c >> 4];
        }
        result.push_back(sum);
        stack.clear();
      }
    }
  }
  if constexpr (solve_part2) {
    auto middle = std::next(std::begin(result), std::size(result) / 2);
    std::ranges::nth_element(result, middle);
    return *middle;
  } else {
    return result;
  }
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
