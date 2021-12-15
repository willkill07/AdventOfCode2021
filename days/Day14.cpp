#include <algorithm>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day14.hpp"

namespace detail {
  using namespace day14;
  using Day = AdventDay<id, parsed, result1, result2>;

}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  
  scn::basic_mapped_file<char> file{filename.c_str()};

  day14::data result;

  constexpr const std::uint8_t MAX = 10;
  constexpr const std::uint8_t UNASSIGNED = -1;
  std::array<std::uint8_t, 26> map;
  map.fill(UNASSIGNED);

  auto lookup = [&] (auto iter) -> std::uint8_t& {
    return map[*iter - 'A'];
  };

  std::uint8_t count{0}; 
  for (char c : file) {
    if (std::isalpha(c) and lookup(&c) == UNASSIGNED) {
      lookup(&c) = count;
      if (++count == MAX) {
        break;
      }
    }
  }

  auto index_fn = [&] (auto a, auto b) {
    return static_cast<std::uint16_t>(lookup(a) * count + lookup(b));
  };

  auto end_of_line = std::find(std::begin(file), std::end(file), '\n');

  result.indices.resize(count * count);
  result.counts.resize(count * count);
  {
    for (auto iter = std::find_if(end_of_line, std::end(file), ::isalpha); iter < std::end(file); iter += 8) {
      day14::index idx {lookup(iter), lookup(iter + 1), lookup(iter + 6)};
      result.indices[idx.self(count)] = idx;
    }
  }

  result.base.assign(count, 0);
  {
    ++result.base[lookup(std::begin(file))];
    for (auto iter = std::begin(file) + 1; iter < end_of_line; ++iter) {
      ++result.counts[index_fn(iter - 1, iter)];
      --result.base[lookup(iter - 1)];
    }
  }
  return result;
}

template <>
template <bool solve_part2> 
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  constexpr const unsigned amount = solve_part2 ? 40 : 10;

  auto base = data.base;
  auto counts = data.counts;
  auto const N = static_cast<std::uint16_t>(std::size(base));

  std::vector<std::int64_t> next(std::size(counts), 0);

  for (unsigned i{0}; i < amount; ++i) {
    for (auto&& idx : data.indices) {
      auto const count = counts[idx.self(N)];
      next[idx.left(N)] += count;
      next[idx.right(N)] += count;
      base[idx.insert_char] -= count;
    }
    std::swap(counts, next);
    std::ranges::fill(next, 0);
  }

  for (auto&& idx : data.indices) {
    base[idx.left_char] += counts[idx.self(N)];
    base[idx.right_char] += counts[idx.self(N)];
  }

  auto&& [min, max] = std::ranges::minmax(base);
  return max - min;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
