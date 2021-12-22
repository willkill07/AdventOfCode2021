#include <scn/all.h>

#include <array>

#include "AdventDay.hpp"
#include "Day21.hpp"

namespace detail {
  using namespace day21;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  auto i = std::find(std::begin(file), std::end(file), '\n');
  auto j = std::find(i + 1, std::end(file), '\n');
  return { *(i - 1) - '0', *(j - 1) - '0' };
}

constexpr inline unsigned
simulate(unsigned pos1, unsigned pos2, unsigned score1 = 0u, unsigned score2 = 0u, unsigned i = 0u, unsigned delta = 6u) {
  if (score2 >= 1000) {
    return i * score1;
  }
  pos1 = (pos1 + delta);
  if (pos1 > 10) {
    pos1 -= 10;
  }
  if (not delta) { // if delta is 0
    delta = 10;
  }
  --delta;
  return simulate(pos2, pos1, score2, score1+pos1, i + 3, delta);
}

constexpr std::array<std::pair<unsigned,unsigned long>, 7> const DIE_OUTCOMES {{ {3u,1lu}, {4u,3lu}, {5u,6lu}, {6u,7lu}, {7u,6lu}, {8u,3lu}, {9u,1lu} }};
constexpr unsigned const POINTS = 21;

inline void
multiverse_simulate(unsigned pos, auto curr, auto end, unsigned remaining = POINTS, unsigned long weight = 1lu) {
  if (curr != end) {
    auto& [wins, losses] = *curr;
    for (auto const& [num, mult] : DIE_OUTCOMES) {
      auto const pos1 = pos + num;
      auto const pos2 = pos1 > 9 ? pos1 - 10 : pos1;
      auto const score = pos2 == 0 ? 10 : pos2;
      auto const unified = mult * weight;
      if (score >= remaining) {
        wins += unified;
      } else {
        losses += unified;
        multiverse_simulate(pos2, curr + 1, end, remaining - score, unified);
      }
    }
  }
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {

  if constexpr (solve_part2) {
    std::array<std::pair<unsigned long, unsigned long>, POINTS> p1, p2;
    p1.fill({0lu, 0lu});
    p2.fill({0lu, 0lu});
    
    multiverse_simulate(data.first, std::begin(p1), std::end(p1));
    multiverse_simulate(data.second, std::begin(p2), std::end(p2));

    return [&] {
      unsigned long r1{0lu}, r2{0lu};
      for (unsigned i{0}; i < POINTS - 1; ++i) {
        r1 += p1[i + 1].first * p2[i].second;
        r2 += p2[i].first * p1[i].second;
      }
      r2 += p2[POINTS - 1].first * p1[POINTS - 1].second;
      return std::max(r1, r2);
    }();
    
  } else {
    return simulate(data.first, data.second);
  }
}


INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
