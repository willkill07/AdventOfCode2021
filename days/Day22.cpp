#include <scn/all.h>

#include <array>
#include <numeric>
#include <ranges>

#include "AdventDay.hpp"
#include "Day22.hpp"

namespace detail {
  using namespace day22;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  Day::parsed_type result;

  auto i = std::begin(file);
  auto end = std::end(file);

  auto advance_to = [&] (char target) {
    i = std::find(i, end, target);
  };

  auto extract_line = [&] {
    auto extract_pair = [&] {
      auto extract_num = [&] {
        bool negate {*i == '-'};
        if (negate) {
          ++i;
        }
        int num{0};
        while (::isdigit(*i)) {
          num = 10 * num + (*i++ - '0');
        }
        return negate ? -num : num;
      };
      advance_to('=');
      ++i;    // skip =
      int const lo = extract_num();
      i += 2; // skip ..
      int const hi = extract_num();
      return std::pair(lo, hi);
    };
    auto [x_lo, x_hi] = extract_pair();
    auto [y_lo, y_hi] = extract_pair();
    auto [z_lo, z_hi] = extract_pair();
    return day22::box{{x_lo, y_lo, z_lo}, {x_hi, y_hi, z_hi}};
  };

  while (true) {
    advance_to('o');
    if (i == end) {
      break;
    }
    bool on = *(++i) == 'n';
    result.push_back({ on, extract_line() });
  }

  return result;
}

template <bool solve_part2>
unsigned long
volume(day22::box const& b) {
  if constexpr (not solve_part2) {
    if (auto& [lx, ly, lz] = b.lo; lx <= -50 or ly <= -50 or lz <= -50) {
      return 0;
    }
    if (auto& [hx, hy, hz] = b.hi; hx >= 50 or hy >= 50 or hz >= 50) {
      return 0;
    }
  }
  auto const diff = b.hi - b.lo;
  return static_cast<unsigned long>(diff.x + 1) *
    static_cast<unsigned long>(diff.y + 1) *
    static_cast<unsigned long>(diff.z + 1);
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  std::vector<day22::box> cubes, next;
  cubes.reserve(4096);
  next.reserve(4096);
  for (auto& [on, curr] : data) {
    for (auto const& c : cubes) {
      if (c.intersects(curr)) {
        day22::box::difference(c, curr, next);
      } else {
        next.push_back(c);
      }
    }
    if (on) {
      next.push_back(curr);
    }
    cubes.swap(next);
    next.clear();
  }

  unsigned long sum{0lu};
  for (auto const& c : cubes) {
    sum += volume<solve_part2>(c);
  }
  return sum;
}


INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
