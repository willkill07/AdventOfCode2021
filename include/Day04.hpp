#pragma once

#include <array>
#include <vector>
#include <string>

#include <scn/all.h>

namespace day04 {

  struct data {
    using board_type = std::array<std::array<int, 5>,5>;
    std::vector<int> nums;
    std::vector<board_type> boards;
  };

  constexpr const int id = 4;
  using parsed = data;
  using result1 = int;
  using result2 = int;
}
