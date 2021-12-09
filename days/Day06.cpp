#include <array>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day06.hpp"

namespace detail {
  using namespace day06;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

using day06::matrix;
using day06::array;
using day06::is_matrix;
using day06::is_array;
using day06::mpow;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  auto to_num = [] (char c) { return static_cast<unsigned>(c - '0'); };
  auto nums = file | std::ranges::views::filter(::isdigit) | std::ranges::views::transform(to_num);
  array<9> res;
  std::ranges::fill(res, 0);
  for (auto&& num : nums) {
    ++res[num];
  }
  return res;
}

template <is_matrix Mat, is_array Arr>
auto
reduce(Mat&& a, Arr&& b) {
  typename std::decay_t<Arr>::value_type c{0};
  for (unsigned i{0}; i < 9; ++i) {
    for (unsigned k{1}; k < 7; ++k) {
      c += a[i][k] * b[k];
    }
  }
  return c;
}

constexpr const matrix<9,9> translation {{
  { 0,1,0,0,0,0,0,0,0 },
  { 0,0,1,0,0,0,0,0,0 },
  { 0,0,0,1,0,0,0,0,0 },
  { 0,0,0,0,1,0,0,0,0 },
  { 0,0,0,0,0,1,0,0,0 },
  { 0,0,0,0,0,0,1,0,0 },
  { 1,0,0,0,0,0,0,1,0 },
  { 0,0,0,0,0,0,0,0,1 },
  { 1,0,0,0,0,0,0,0,0 }
}};

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& lanternfish, Day::opt_answer) {
  return reduce(mpow(translation, solve_part2 ? 256 : 80), lanternfish);
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
