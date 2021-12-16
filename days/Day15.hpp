#pragma once

#include <algorithm>
#include <type_traits>
#include <vector>

namespace day15 {

  struct grid {
    std::vector<std::uint8_t> data;
    unsigned w, h;
    
    template <unsigned Rep>
    unsigned width() const {
      return Rep * w;
    }
    
    template <unsigned Rep>
    unsigned height() const {
      return Rep * h;
    }

    template <unsigned Rep>
    std::uint8_t get(unsigned row, unsigned col) const {
      if constexpr (Rep == 1) {
        return data[row * w + col];
      } else {
        unsigned r{row}, c{col}, dist{0};
        for (; r >= h; r -= h) {
          ++dist;
        }
        for (; c >= w; c -= w) {
          ++dist;
        }
        return static_cast<std::uint8_t>((data[r * w + c] - 1 + dist) % 9 + 1);
      }
    }
  };

  constexpr const int id = 15;
  using parsed = grid;

  template <bool part2>
  using answer = long;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
