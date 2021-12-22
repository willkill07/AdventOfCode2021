#pragma once

#include <type_traits>
#include <utility>

namespace day21 {

  constexpr const int id = 21;
  using parsed = std::pair<unsigned, unsigned>;

  template <bool part2>
  using answer = std::conditional_t<part2, unsigned long, unsigned>;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
