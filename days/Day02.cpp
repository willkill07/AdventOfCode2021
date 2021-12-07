#include <ranges>
#include <utility>
#include <vector>

#include "AdventDay.hpp"
#include "Day02.hpp"
#include "Scanner.hpp"

namespace detail {
  using namespace day02;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
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
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  std::conditional_t<solve_part2, p2, p1> state;
  for (auto const& cmd : data) {
    state = update(state, cmd);
  }
  return state.x * state.y;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
