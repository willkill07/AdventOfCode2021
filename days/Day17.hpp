#pragma once

namespace day17 {

  struct range {
    int lo, hi;
  };

  struct data {
    range x, y;
  };

  constexpr const int id = 17;
  using parsed = data;

  template <bool part2>
  using answer = int;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
