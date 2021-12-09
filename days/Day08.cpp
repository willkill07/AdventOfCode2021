#include <algorithm>
#include <bitset>
#include <cctype>
#include <limits>
#include <numeric>
#include <ranges>
#include <vector>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day08.hpp"

namespace detail {
  using namespace day08;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  Day::parsed_type result;
  result.reserve(200);
  for (auto i = file.begin(); i < file.end(); ++i) {
    Day::parsed_type::value_type temp;
    
    for (auto& num : temp.lookup) {
      while (not std::isalpha(*i)) {
        ++i;
      }
      num.reset();
      while (std::isalpha(*i)) {
        num.set(*i - 'a');
        ++i;
      }
    }

    for (auto& num : temp.output) {
      while (not std::isalpha(*i)) {
        ++i;
      }
      num.reset();
      while (std::isalpha(*i)) {
        num.set(*i - 'a');
        ++i;
      }
    }

    result.push_back(temp);
  }
  return result;
}

std::array<unsigned, 10>
make_lookup(std::array<std::bitset<7>,10> const& numbers) {
  std::array<unsigned, 10> map{};
  std::array<unsigned, 10> rev{};
  for (unsigned i{0}; auto&& n : numbers) {
    switch (n.count()) {
      case 2: map[1] = i; rev[i] = 1; break;
      case 3: map[7] = i; rev[i] = 7; break;
      case 4: map[4] = i; rev[i] = 4; break;
      case 7: map[8] = i; rev[i] = 8; break;
      default: break;
    }
    ++i;
  }
  for (unsigned i{0}; auto&& n : numbers) {
    switch (n.count()) {
      case 5:
        if ((n & numbers[map[7]]).count() == 3) {
          rev[i] = 3;
        } else if ((n & numbers[map[4]]).count() == 3) {
          rev[i] = 5;
        } else {
          rev[i] = 2;
        }
        break;
      case 6:
        if ((n & numbers[map[4]]).count() == 4) {
          rev[i] = 9;
        } else if ((n & numbers[map[7]]).count() == 3) {
          rev[i] = 0;
        } else {
          rev[i] = 6;
        }
        break;
      default: break;
    }
    ++i;
  }
  return rev;
}

int
make_number(std::array<unsigned, 10> const& lookup, auto&& entry) {
  int num{0};
  auto const begin = std::begin(entry.lookup);
  for (auto&& v : entry.output) {
    num = 10 * num + lookup[std::distance(begin, std::ranges::find(entry.lookup, v))];
  }
  return num;
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  int count{0};
  for (auto&& entry : data) {
    if constexpr (solve_part2) {
      auto const lookup = make_lookup(entry.lookup);
      count += make_number(lookup, entry);
    } else {
      for (auto&& v : entry.output) {
        if (auto c = v.count(); c != 5 and c != 6) {
          ++count;
        }
      }
    }
  }
  return count;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
