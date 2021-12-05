#include <algorithm>
#include <functional>
#include <numeric>
#include <ranges>
#include <utility>
#include <vector>

#include "AdventDay.hpp"
#include "Day03.hpp"
#include "Scanner.hpp"

using Day = AdventDay<day03::id, day03::parsed, day03::result1, day03::result2>;

using parsed_type = typename Day::parsed_type;
using part1_opt = std::optional<typename Day::answer_one_type>;

template <bool part2>
using answer = std::conditional_t<part2, typename Day::answer_two_type, typename Day::answer_one_type>;

unsigned
get_width(parsed_type const& all) {
  auto most_set = std::accumulate(all.begin(), all.end(), parsed_type::value_type{}, std::bit_or<>{});
  for (unsigned count{1}; true ; ++count) {
    most_set >>= 1;
    if (not most_set.any()) {
      return count;
    }
  }
}

template <>
parsed_type
Day::parse(char const* filename) {
  scn::basic_mapped_file<char> file{filename};
  std::vector<std::string> result;
  result.reserve(1000);
  scn::scan_list(file, result, '\n');
  for (auto& v : result) {
    std::ranges::reverse(v);
  }
  parsed_type out;
  out.reserve(std::size(result));
  for (auto& v : result) {
    out.push_back(parsed_type::value_type{v});
  }
  return out;
}

auto getter(auto i) {
  return [i] (auto& v) {
    return v[i];
  };
}

auto excluder(auto i, auto target) {
  return [=] (auto& v) {
    return target == v[i];
  };
};

bool majority(auto num, auto total) {
  return 2 * num >= total;
}

int to_number(auto& v, auto width) {
  int result{0};
  for (decltype(width) i{0}; i < width; ++i) {
    result |= (v[i] << (width - i - 1));
  }
  return result;
};

template <>
template <bool solve_part2>
answer<solve_part2>
Day::solve(parsed_type const& data, part1_opt) {

  auto const total = std::ssize(data);
  auto const width = get_width(data);

  if constexpr (!solve_part2) {
    int gamma{0}, epsilon{0};
    for (unsigned i{0}; i < width; ++i) {
      bool const on = majority(std::ranges::count_if(data, getter(i)), total);
      gamma = (gamma << 1) + (on);
      epsilon = (epsilon << 1) + (not on);
    }
    return gamma * epsilon;
  } else {
    parsed_type O2 {data}, CO2 {data};
    auto process = [width] (auto info, bool negate) -> int {
      auto begin = std::begin(info), end = std::end(info);
      for (unsigned i{0}; i < width; ++i) {
        if (auto const size = std::distance(begin, end); size > 1) {
          end = std::remove_if(begin, end, excluder(i, negate ^ majority(std::count_if(begin, end, getter(i)), size)));
        }
      }
      return to_number(*begin, width);
    };
    return process(data, false) * process(data, true);
  }
  return 0;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
