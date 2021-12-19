#pragma once

#include <list>
#include <vector>

namespace day18 {

  using SnailNumber = std::vector<std::pair<int,int>>;

  constexpr const int id = 18;
  using parsed = std::vector<SnailNumber>;

  template <bool part2>
  using answer = int;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
