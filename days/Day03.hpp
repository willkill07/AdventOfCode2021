#pragma once

#include <bitset>
#include <vector>

namespace day03 {
  constexpr const int id = 3;
  using parsed = std::vector<std::bitset<16>>;

  template <bool part2>
  using answer = int;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
