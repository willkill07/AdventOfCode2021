#include <ranges>
#include <utility>
#include <vector>

#include "AdventDay.hpp"
#include "Day01.hpp"
#include "Scanner.hpp"

using namespace day01;
using Day = AdventDay<id, parsed, result1, result2>;
using opt_answer = Day::opt_answer;

template <>
parsed
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  std::vector<int> result;
  result.reserve(2000);
  scn::scan_list(file, result, '\n');
  return result;
}

template <>
template <bool solve_part2>
typename Day::answer<solve_part2>
Day::solve(parsed const& data, opt_answer) {
  constexpr std::size_t N = solve_part2 ? 3 : 1;
  int count{0};
  for (std::size_t i{N}; i < std::size(data); ++i)
    if (data[i] > data[i - N])
      ++count;
  return count;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
