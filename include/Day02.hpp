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
  using result1 = int;
  using result2 = long;
}
