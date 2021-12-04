#include <algorithm>
#include <numeric>
#include <ranges>
#include <utility>
#include <vector>

#include "AdventDays.hpp"

using Day = get_day<3>;

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

template <>
template <bool solve_part2>
answer<solve_part2>
Day::solve(parsed_type const& data, part1_opt) {
  using type = typename parsed_type::value_type::type;
  type val;
  for (auto& v : data) {
    val |= v.data;
  }
  unsigned const width = static_cast<unsigned>(val.count());
  unsigned const total = static_cast<unsigned>(std::size(data));
  if constexpr (!solve_part2) {
    int gamma{0};
    int epsilon{0};
    for (unsigned i{0}; i < width; ++i) {
      unsigned const set = static_cast<unsigned>(std::ranges::count_if(data, [i] (auto& v) { return v.data[i]; }));
      bool const majority_set = 2 * set > total;
      bool const minority_set = not majority_set;
      gamma = (gamma << 1) + +(majority_set);
      epsilon = (epsilon << 1) + +(minority_set);
    }
    return gamma * epsilon;
  } else {
    parsed_type O_list {data.begin(), data.end()};
    parsed_type CO2_list {data.begin(), data.end()};

    for (unsigned i{0}; i < width; ++i) {
      unsigned const set = static_cast<unsigned>(std::ranges::count_if(O_list, [&] (auto& v) { return v.data[i]; }));
      bool const majority_set = 2 * set >= std::size(O_list);
      O_list.remove_if([&] (auto& v) { return majority_set == v.data[i]; });
      if (std::size(O_list) == 1) {
        break;
      }
    }
    for (unsigned i{0}; i < width; ++i) {
      unsigned const set = static_cast<unsigned>(std::ranges::count_if(CO2_list, [&] (auto& v) { return v.data[i]; }));
      bool const majority_set = 2 * set >= std::size(CO2_list);
      CO2_list.remove_if([&] (auto& v) { return majority_set != v.data[i]; });
      if (std::size(CO2_list) == 1) {
        break;
      }
    }
    auto extract_value = [width] (auto& v) {
      int result{0};
      for (unsigned i{0}; i < width; ++i) {
        result |= (v[i] << (width - i - 1));
      }
      return result;
    };
    return extract_value(O_list.front().data) * extract_value(CO2_list.front().data);
  }
  return 0;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
