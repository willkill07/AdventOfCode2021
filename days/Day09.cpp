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
#include "Day09.hpp"

namespace detail {
  using namespace day09;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  return day09::matrix(file.buffer());
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  if constexpr (not solve_part2) {
    int total{0};
    for (unsigned r{0}; r < data.height(); ++r) {
      for (unsigned c{0}; c < data.width(); ++c) {
        auto const curr = data(r, c);
        if ((r == 0 or curr < data(r - 1, c)) and (r == data.height() - 1 or curr < data(r + 1, c)) and
            (c == 0 or curr < data(r, c - 1)) and (c == data.width() - 1  or curr < data(r, c + 1))) {
              total += (curr - '0' + 1);
            }
      }
    }
    return total;
  } else {
    day09::matrix copy{data};
    std::vector<std::pair<unsigned,unsigned>> queue;
    queue.reserve(copy.size() / 2);
    std::vector<unsigned> basin_sizes;
    for (unsigned R{0}; R < copy.height(); ++R) {
      for (unsigned C{0}; C < copy.width(); ++C) {
        if (auto const curr = copy(R, C); curr != '9') {
          unsigned visited{0};
          queue.clear();
          queue.push_back({R , C});
          while (not queue.empty()) {
            auto [y, x] = queue.back();
            queue.pop_back();
            if (copy(y, x) != '9') {
              copy(y, x) = '9'; ++visited;
              if (y > 0                 and copy(y - 1, x) != '9') queue.push_back({y - 1, x});
              if (x > 0                 and copy(y, x - 1) != '9') queue.push_back({y, x - 1});
              if (y < copy.height() - 1 and copy(y + 1, x) != '9') queue.push_back({y + 1, x});
              if (x < copy.width() - 1  and copy(y, x + 1) != '9') queue.push_back({y, x + 1});
            }
          }
          basin_sizes.push_back(visited);
        }
      }
    }
    
    std::ranges::sort(basin_sizes);
    auto rng = basin_sizes | std::views::reverse | std::views::take(3) | std::views::common;
    return std::accumulate(std::ranges::begin(rng), std::ranges::end(rng), 1, std::multiplies<>{});
  }
  return 0;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
