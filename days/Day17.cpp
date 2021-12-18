#include <cmath>
#include <utility>
#include <vector>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day17.hpp"

namespace detail {
  using namespace day17;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  day17::data result;
  auto parse_int = [] (auto& i) {
    for (; not ::isdigit(*i); ++i)
      ;
    bool const negate = (*(i - 1) == '-');
    int value{0};
    for (; ::isdigit(*i); ++i) {
      value = 10 * value + (*i - '0');
    }
    return (negate ? -value : value);
  };
  auto i = std::begin(file);
  result.x.lo = parse_int(i);
  result.x.hi = parse_int(i);
  result.y.lo = parse_int(i);
  result.y.hi = parse_int(i);
  return result;
}

namespace {

int
inverse_triangular(int x) {
  return static_cast<int>(std::sqrt(2.0 * x));
}

bool
check(int vx, int vy, int xmin, int xmax, int ymin, int ymax) {
  int x{0}, y{0};
  while (x <= xmax and ymin <= y) {
    if (xmin <= x and y <= ymax) {
      return true;
    }
    x += vx;
    y += vy--;
    if (--vx < 0) {
      vx = 0;
    }
  }
  return false;
}

int
exhaustive_search(int xmin, int xmax, int ymin, int ymax) {
  int total{0};
  for (int vx{inverse_triangular(xmin)}; vx <= xmax; ++vx) {
    for (int vy{ymin}; vy < -ymin; ++vy) {
      if (check(vx, vy, xmin, xmax, ymin, ymax)) {
        ++total;
      }
    }
  }
  return total;
}

}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  if constexpr (solve_part2) {
    return exhaustive_search(data.x.lo, data.x.hi, data.y.lo, data.y.hi);
  } else {
    return (data.y.lo) * (data.y.lo + 1) / 2;
  }
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
