#pragma once

#include <vector>

namespace day07 {
  constexpr const int id = 7;
  using parsed = std::vector<int>;

  template <bool part2>
  using answer = int;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
