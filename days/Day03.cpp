#include <algorithm>
#include <numeric>
#include <ranges>
#include <utility>
#include <vector>
#include <functional>

#include "AdventDay.hpp"
#include "Day03.hpp"
#include "Scanner.hpp"

using Day = AdventDay<day03::id, day03::parsed, day03::result1, day03::result2>;

using parsed_type = typename Day::parsed_type;
using part1_opt = std::optional<typename Day::answer_one_type>;

template <bool part2>
using answer = std::conditional_t<part2, typename Day::answer_two_type, typename Day::answer_one_type>;

template <>
parsed_type
Day::parse(char const* filename) {
  scn::basic_mapped_file<char> file{filename};
  std::list<day03::data> result;
  scn::scan_list(file, result, '\n');
  return result;
}

auto getter(auto i) {
  return [i] (auto& v) {
    return v.data[i];
  };
}

auto excluder(auto i, auto target) {
  return [=] (auto& v) {
    return target == v.data[i];
  };
};

bool majority(auto num, auto total) {
  return 2 * num >= total;
}

int to_number(auto& v, auto width) {
  int result{0};
  for (decltype(width) i{0}; i < width; ++i) {
    result |= (v.data[i] << (width - i - 1));
  }
  return result;
};

template <>
template <bool solve_part2>
answer<solve_part2>
Day::solve(parsed_type const& data, part1_opt) {
  using element = typename parsed_type::value_type;
  using type = typename element::type;

  auto const total = std::ssize(data);
  auto const width = [&] {
    auto mapped = std::ranges::transform_view(data, &element::data);
    return std::accumulate(mapped.begin(), mapped.end(), type{}, std::bit_or<>{}).count();
  }();

  if constexpr (!solve_part2) {
    int gamma{0};
    int epsilon{0};
    for (unsigned i{0}; i < width; ++i) {
      auto const set = std::ranges::count_if(data, getter(i));
      bool const on = majority(set, total);
      gamma = (gamma << 1) + (on);
      epsilon = (epsilon << 1) + (not on);
    }
    return gamma * epsilon;
  } else {
    parsed_type O2 {data}, CO2 {data};
    for (unsigned i{0}; i < width; ++i) {
      if (auto const size = std::ranges::ssize(O2); size > 1) {
        O2.remove_if(excluder(i, majority(std::ranges::count_if(O2, getter(i)), size)));
      }
    }
    for (unsigned i{0}; i < width; ++i) {
      if (auto const size = std::ranges::ssize(CO2); size > 1) {
        CO2.remove_if(excluder(i, not majority(std::ranges::count_if(CO2, getter(i)), size)));
      }
    }
    return to_number(O2.front(), width) * to_number(CO2.front(), width);
  }
  return 0;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
