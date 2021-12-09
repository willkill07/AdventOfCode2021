#include <cctype>
#include <ranges>
#include <utility>
#include <vector>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day02.hpp"

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
  for (auto i = file.begin(); i != file.end(); ++i) {
    day02::data tmp;
    switch (*i) {
      case 'f': tmp.d = day02::dir::forward; break;
      case 'u': tmp.d = day02::dir::up; break;
      case 'd': tmp.d = day02::dir::down; break;
      default: return result;
    }
    while (!::isspace(*i++));
    int num{0};
    while (::isdigit(*i)) {
      num = 10 * num + (*i++ - '0');
    }
    tmp.amount = num;
    result.push_back(tmp);
  }
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
