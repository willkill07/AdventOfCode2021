#include <algorithm>
#include <limits>
#include <numeric>
#include <ranges>
#include <vector>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day07.hpp"

namespace detail {
  using namespace day07;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  std::vector<int> result;
  result.reserve(1000);
  int num{0};
  for (auto&& c : file) {
    if (::isdigit(c)) {
      num = 10 * num + (c - '0');
    } else {
      result.push_back(std::exchange(num, 0));
    }
  }
  if (num != 0) {
    result.push_back(num);
  }
  return result;
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {

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

  // wanted to have a mutable lambda with min local, but that doesn't compile
  int min {std::numeric_limits<int>::max()};
  auto decreasing = [&] (int curr) {
    return (curr == (min = std::min(min, curr)));
  };

  return (std::ranges::views::iota(std::ranges::min(data))
          | std::ranges::views::transform(get_cost)
          | std::ranges::views::take_while(decreasing)
          | std::ranges::views::reverse
         ).front();
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
