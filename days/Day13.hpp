#pragma once

#include <array>
#include <algorithm>
#include <string>
#include <type_traits>

namespace day13 {

  enum class axis {
    x, y
  };

  struct data {
    std::vector<std::pair<int,int>> points;
    std::vector<std::pair<axis,int>> folds;
  };

  constexpr const int id = 13;
  using parsed = data;

  template <bool part2>
  using answer = std::conditional_t<part2, std::string, long>;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
