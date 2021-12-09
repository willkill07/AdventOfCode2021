#pragma once

#include <array>
#include <bitset>
#include <cstdint>
#include <vector>

namespace day08 {

  using display = std::bitset<7>;

  struct entry {
    std::array<display, 10> lookup;
    std::array<display, 4> output;
  };

  constexpr const int id = 8;
  using parsed = std::vector<entry>;

  template <bool part2>
  using answer = int;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
