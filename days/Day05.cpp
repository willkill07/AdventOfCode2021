#include <array>
#include <ranges>

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
  for (auto&& e : result) {
    if (e.dst > e.src) {
      std::swap(e.src, e.dst);
    }
  }
  std::sort(result.begin(), result.end());
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
  return (a < b) ? 1 : ((a == b) ? 0 : -1);
}

constexpr inline day05::point
delta_of(day05::point const& a, day05::point const& b) {
  return { delta_of(a.x, b.x), delta_of(a.y, b.y) };
}

template <>
template <bool solve_part2>
answer<solve_part2>
Day::solve(parsed_type const& data, part1_opt) {
  std::array<std::array<int,1'000>,1'000> board { {{0}} };
  int total{0};
  for (auto&& [src, dst] : data) {
    if (valid<solve_part2>({src, dst})) {
      day05::point const delta = delta_of(src, dst);
      for (auto loc = src; loc != dst; loc += delta) {
        if (++board[loc.y][loc.x] == 2)
          ++total;
      }
      if (++board[dst.y][dst.x] == 2)
        ++total;
    }
  }
  return total;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
