#pragma once

#include <array>
#include <algorithm>
#include <ranges>

namespace day11 {

  using board = std::array<std::array<int,12>,12>;

  constexpr const int id = 11;
  using parsed = board;

  template <bool part2>
  using answer = unsigned;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
