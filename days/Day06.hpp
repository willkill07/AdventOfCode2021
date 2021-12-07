#pragma once

#include <vector>

namespace day06 {

  constexpr const int id = 6;
  using parsed = std::vector<unsigned>;

  template <bool part2>
  using answer = unsigned long long;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
