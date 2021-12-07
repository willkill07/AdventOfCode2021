#include <algorithm>
#include <bits/ranges_algo.h>
#include <limits>
#include <numeric>
#include <ranges>
#include <utility>
#include <vector>

#include "AdventDay.hpp"
#include "Day07.hpp"
#include "Scanner.hpp"

using namespace day07;
using Day = AdventDay<id, parsed, result1, result2>;
using opt_answer = Day::opt_answer;

template <>
parsed
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  std::vector<int> result;
  result.reserve(1000);
  scn::scan_list(file, result, ',');
  return result;
}

template <>
template <bool solve_part2>
typename Day::answer<solve_part2>
Day::solve(parsed const& data, opt_answer) {
  
  auto cost_fn = [] (int loc) {
    return [loc] (int x) {
      if constexpr (int const diff = std::abs(x - loc); solve_part2) {
        return (diff + 1) * diff / 2;
      } else {
        return diff;
      }
    };
  };

  auto get_cost = [&] (int x) {
    auto const deltas = data | std::ranges::views::transform(cost_fn(x));
    return std::accumulate(std::ranges::begin(deltas), std::ranges::end(deltas), 0);
  };

  int min {std::numeric_limits<int>::max()};
  auto decreasing = [&] (int curr) {
    return (curr == (min = std::min(min, curr)));
  };

  return (
    std::ranges::views::iota(std::ranges::min(data))
    | std::ranges::views::transform(get_cost)
    | std::ranges::views::take_while(decreasing) // find the minimum
    | std::ranges::views::reverse
    ).front();
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
