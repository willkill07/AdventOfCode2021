#include <array>
#include <cctype>
#include <numeric>
#include <ranges>
#include <vector>

#include "AdventDay.hpp"
#include "Day06.hpp"
#include "Scanner.hpp"

using namespace day06;
using Day = AdventDay<id, parsed, result1, result2>;
using opt_answer = Day::opt_answer;

template <>
parsed
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  auto to_num = [] (char c) { return static_cast<unsigned>(c - '0'); };
  auto vals = file | std::ranges::views::filter(::isdigit) | std::ranges::views::transform(to_num);
  return { std::ranges::begin(vals), std::ranges::end(vals) };
}

constexpr const unsigned timer = 7;
constexpr const unsigned total = timer + 2;

template <>
template <bool solve_part2>
typename Day::answer<solve_part2>
Day::solve(parsed const& data, opt_answer) {

  constexpr const int days = solve_part2 ? 256 : 80;

  std::array<unsigned long long, total> lanternfish {0};
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
