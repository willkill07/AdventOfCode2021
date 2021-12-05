#include <algorithm>
#include <array>
#include <ranges>
#include <vector>

#include "AdventDay.hpp"
#include "Day05.hpp"
#include "Scanner.hpp"

using Day = AdventDay<day05::id, day05::parsed, day05::result1, day05::result2>;

using parsed_type = typename Day::parsed_type;
using part1_opt = std::optional<typename Day::answer_one_type>;

template <bool part2>
using answer = std::conditional_t<part2, typename Day::answer_two_type, typename Day::answer_one_type>;

template <>
parsed_type
Day::parse(char const* filename) {
  scn::basic_mapped_file<char> file{filename};
  parsed_type result;
  scn::scan_list(file, result, '\n');
  return result;
}

template <bool solve_part2>
bool
valid (day05::edge const& e) {
  if constexpr(day05::point d = (e.src - e.dst); solve_part2) {
    return d.straight() or d.diagonal();
  } else {
    return d.straight();
  }
}

constexpr inline int
delta_of(int a, int b) {
  if (a < b) {
    return 1;
  } else if (a > b) {
    return -1;
  } else {
    return 0;
  }
}

template <>
template <bool solve_part2>
answer<solve_part2>
Day::solve(parsed_type const& data, part1_opt) {
  std::array<std::array<int,1'000>,1'000> board { 0 };
  int total{0};
  for (auto&& [src, dst] : data) {
    if (valid<solve_part2>({src, dst})) {
      day05::point const delta = { delta_of(src.x, dst.x), delta_of(src.y, dst.y) };
      for (auto loc = src; loc != dst; loc += delta) {
        total += +(++board[loc.y][loc.x] == 2);
      }
      if (board[dst.y][dst.x] < 2) {
        total += +(++board[dst.y][dst.x] == 2);
      }
    }
  }
  return total;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
