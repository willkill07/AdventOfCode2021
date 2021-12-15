#pragma once

#include <array>
#include <algorithm>
#include <type_traits>
#include <vector>

namespace day14 {

  struct index {
    std::uint8_t left_char, right_char, insert_char;
    
    inline unsigned left(unsigned count) const {
      return left_char * count + insert_char;
    }
    inline unsigned right(unsigned count) const {
      return insert_char * count + right_char;
    }
    inline unsigned self(unsigned count) const {
      return left_char * count + right_char;
    }
  };

  struct data {
    std::vector<std::int64_t> counts, base;
    std::vector<index> indices;
  };

  constexpr const int id = 14;
  using parsed = data;

  template <bool part2>
  using answer = long;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
