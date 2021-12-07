#include <ranges>
#include <utility>
#include <vector>

#include "AdventDay.hpp"
#include "Day01.hpp"
#include "Scanner.hpp"

namespace detail {
  using namespace day01;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  std::vector<int> result;
  result.reserve(2000);
  scn::scan_list(file, result, '\n');
  return result;
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  constexpr std::size_t N = solve_part2 ? 3 : 1;
  int count{0};
  for (std::size_t i{N}; i < std::size(data); ++i)
    if (data[i] > data[i - N])
      ++count;
  return count;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
