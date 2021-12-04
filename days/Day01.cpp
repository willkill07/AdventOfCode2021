#include <algorithm>
#include <numeric>
#include <ranges>
#include <utility>
#include <vector>

#include "AdventDay.hpp"
#include "Day01.hpp"
#include "Scanner.hpp"


using Day = AdventDay<day01::id, day01::parsed, day01::result1, day01::result2>;

using parsed_type = typename Day::parsed_type;
using part1_opt = std::optional<typename Day::answer_one_type>;

template <bool part2>
using answer = std::conditional_t<part2, typename Day::answer_two_type, typename Day::answer_one_type>;

template <>
parsed_type
Day::parse(char const* filename) {
  scn::basic_mapped_file<char> file{filename};
  std::vector<int> result;
  result.reserve(2000);
  scn::scan_list(file, result, '\n');
  return result;
}

template <>
template <bool solve_part2>
answer<solve_part2>
Day::solve(parsed_type const& data, part1_opt) {
  constexpr std::size_t N = solve_part2 ? 3 : 1;
  int count{0};
  for (std::size_t i{N}; i < std::size(data); ++i)
    if (data[i] > data[i - N])
      ++count;
  return count;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
