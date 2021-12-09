#pragma once

#include <vector>
#include <string>

namespace day02 {
  enum class dir {
    up,
    down,
    forward
  };

  struct data {
    dir d;
    int amount;
  };
  
  constexpr const int id = 2;
  using parsed = std::vector<data>;

  template <bool part2>
  using answer = int;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
