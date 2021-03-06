#include <array>
#include <ranges>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day05.hpp"

namespace detail {
  using namespace day05;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  Day::parsed_type result;

  auto read_number = [] (auto& itr) {
    int num{0};
    while(not std::isdigit(*itr)) {
      ++itr;
    }
    while(std::isdigit(*itr)) {
      num = 10 * num + (*itr - '0');
      ++itr;
    }
    return num;
  };

  for (auto i = file.begin(); i < file.end(); ) {
    day05::edge e;
    e.src.x = read_number(i);
    e.src.y = read_number(i);
    e.dst.x = read_number(i);
    e.dst.y = read_number(i);
    if (e.dst < e.src) {
      std::swap(e.src, e.dst);
    }
    result.push_back(e);
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
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  std::array<std::array<int,1'000>,1'000> board;
  std::ranges::fill(board[0], 0);
  std::ranges::fill(board, board[0]);

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
