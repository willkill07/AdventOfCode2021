#include <algorithm>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day13.hpp"

namespace detail {
  using namespace day13;
  using Day = AdventDay<id, parsed, result1, result2>;

  char convert_to_char(std::uint64_t hash) {
    static std::unordered_map<std::uint64_t,char> const letter_mapping {{
      { 0x000000001e11110fllu, 'Z' },
      { 0x000000000c94a529llu, 'U' },
      { 0x000000000c94210cllu, 'J' },
      { 0x000000001297a526llu, 'A' },
      { 0x0000000002109c2fllu, 'F' },
      { 0x000000001294bd29llu, 'H' },
      { 0x000000000213a527llu, 'P' },
      { 0x0000000001f8c63fllu, 'O' }
    }};
    return letter_mapping.at(hash);
  }
}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  day13::data result;
  auto i = std::begin(file); 
  auto get_num = [&] {
      int num{0};
      while (!std::isdigit(*i)) {
        ++i;
      }
      while (std::isdigit(*i)) {
        num = num * 10 + (*i++ - '0');
      }
      return num;
    };

  while (i < std::end(file)) {
    if (!std::isdigit(*i)) {
      break;
    }
    int x = get_num();
    ++i; // comma
    int y = get_num();
    ++i; // newline
    result.points.push_back({x, y});
  }
  while (i < std::end(file)) {
    while(*++i != ' ');
    while(*++i != ' ');
    day13::axis axis{*++i == 'x' ? day13::axis::x : day13::axis::y};
    ++i; // equals
    int amount = get_num();
    ++i; // newline
    result.folds.push_back({axis, amount});
  }
  return result;
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  auto points = data.points;
  if constexpr(solve_part2) {
    for (auto&& [axis, amount] : data.folds) {
      for (auto&& [x,y] : points) {
        if (axis == day13::axis::x) {
          if (x > amount) {
            x = 2 * amount - x;
          }
        } else {
          if (y > amount) {
            y = 2 * amount - y;
          }
        }
      }
    }

    auto const min_x = std::ranges::min(points, std::less<>{}, &std::pair<int,int>::first).first;
    auto const min_y = std::ranges::min(points, std::less<>{}, &std::pair<int,int>::second).second;
    auto const max_x = std::ranges::max(points, std::less<>{}, &std::pair<int,int>::first).first;
    auto const width = static_cast<unsigned>(max_x - min_x + 2);

    std::vector<std::uint64_t> all(width / 5, 0llu);
    for (auto [x, y] : points) {
      all[(x - min_x) / 5] |= (1llu << ((y - min_y) * 5 + ((x - min_x) % 5)));
    }
    auto rng = all | std::views::transform(detail::convert_to_char);
    return std::string(std::begin(rng), std::end(rng));
  } else {
    auto [axis, amount] = data.folds.front();
    if (axis == day13::axis::x) {
      for (auto&& [x,y] : points) {
        if (x > amount) {
          x = 2 * amount - x;
        }
      }
    } else {
      for (auto& [x,y] : points) {
        if (y > amount) {
          y = 2 * amount - y;
        }
      }
    }
    std::ranges::sort(points);
    return std::distance(std::begin(points), std::unique(std::begin(points), std::end(points)));
  }
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
