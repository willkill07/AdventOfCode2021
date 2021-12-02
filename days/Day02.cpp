#include <algorithm>
#include <numeric>
#include <ranges>
#include <utility>
#include <vector>

#include "AdventDays.hpp"
#include "Day02.hpp"

using Day = get_day<2>;

using parsed_type = typename Day::parsed_type;
using part1_opt = std::optional<typename Day::answer_one_type>;

template <bool part2>
using answer = std::conditional_t<part2, typename Day::answer_two_type, typename Day::answer_one_type>;

template <>
parsed_type
Day::parse(char const* filename) {
  scn::basic_mapped_file<char> file{filename};
  std::vector<day02::data> result;
  scn::scan_list(file, result, '\n');
  return result;
}

auto
update_part1(int x, int y, auto v) {
  using day02::dir;
  switch (v.d) {
    case dir::up:   return std::make_tuple(x, y - v.amount);
    case dir::down: return std::make_tuple(x, y + v.amount);
    default:        return std::make_tuple(x + v.amount, y);
  }
}

auto
update_part2(long x, long y, long aim, auto v) {
  using day02::dir;
  switch (v.d) {
    case dir::up:   return std::make_tuple(x, y, aim - v.amount);
    case dir::down: return std::make_tuple(x, y, aim + v.amount);
    default:        return std::make_tuple(x + v.amount, y + aim * v.amount, aim);
  }
}

template <>
template <bool solve_part2>
answer<solve_part2>
Day::solve(parsed_type const& data, part1_opt) {
  using res = std::conditional_t<solve_part2, long, int>;
  res x{0}, y{0}, aim{0};
  for (auto cmd : data) {
    if constexpr (solve_part2) {
      std::tie(x, y, aim) = update_part2(x, y, aim, cmd);
    } else {
      std::tie(x, y) = update_part1(x, y, cmd);
    }
  }
  return x * y;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
