#include <vector>
#include <numeric>

#include "AdventDay.hpp"
#include "Day06.hpp"
#include "Scanner.hpp"


using Day = AdventDay<day06::id, day06::parsed, day06::result1, day06::result2>;

using parsed_type = typename Day::parsed_type;
using part1_opt = std::optional<typename Day::answer_one_type>;

template <bool part2>
using answer = std::conditional_t<part2, typename Day::answer_two_type, typename Day::answer_one_type>;

template <>
parsed_type
Day::parse(char const* filename) {
  scn::basic_mapped_file<char> file{filename};
  std::vector<unsigned> result;
  result.reserve(2000);
  scn::scan_list(file, result, ',');
  return result;
}

constexpr const unsigned timer = 7;
constexpr const unsigned total = timer + 2;

template <>
template <bool solve_part2>
answer<solve_part2>
Day::solve(parsed_type const& data, part1_opt) {

  constexpr const int days = solve_part2 ? 256 : 80;

  std::vector<unsigned long long> lanternfish (total);
  for (unsigned t : data) {
    ++lanternfish[t];
  }

  for (unsigned day{1}; day <= days; ++day) {
    unsigned const idx = (day + timer - 1) % total;
    unsigned const next_idx = (day + timer + 1) % total;
    lanternfish[idx] += lanternfish[next_idx];
  }

	return std::accumulate(std::begin(lanternfish), std::end(lanternfish), 0llu);
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
