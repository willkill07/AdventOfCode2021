#pragma once

#include <array>
#include <vector>

namespace day04 {

  using board_type = std::array<std::array<int, 5>,5>;

  struct data {
    std::vector<int> nums;
    std::vector<board_type> boards;
  };

  constexpr const int id = 4;
  using parsed = data;

  template <bool part2>
  using answer = int;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
