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

struct p1 {
  int x{0}, y{0};
};

struct p2 {
  int x{0}, y{0}, aim{0};
};

p1
update(p1 const& s, day02::data const& v) {
  using day02::dir;
  switch (v.d) {
    case dir::up:   return { s.x, s.y - v.amount };
    case dir::down: return { s.x, s.y + v.amount };
    default:        return { s.x + v.amount, s.y };
  }
}

p2
update (p2 const& s, day02::data const& v) {
  using day02::dir;
  switch (v.d) {
    case dir::up:   return { s.x, s.y, s.aim - v.amount };
    case dir::down: return { s.x, s.y, s.aim + v.amount };
    default:        return { s.x + v.amount, s.y + s.aim * v.amount, s.aim };
  }
}

template <>
template <bool solve_part2>
answer<solve_part2>
Day::solve(parsed_type const& data, part1_opt) {
  std::conditional_t<solve_part2, p2, p1> state;
  for (auto const& cmd : data) {
    state = update(state, cmd);
  }
  return state.x * state.y;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
