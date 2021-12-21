#pragma once

#include <array>
#include <bitset>
#include <ranges>
#include <numeric>

namespace day20 {

  template <int H, int W>
  struct bit_matrix {

    inline bit_matrix(int vheight, int vwidth)
    : base_x{(W - vwidth) / 2}
    , base_y{(H - vheight) / 2}
    , width{vwidth}
    , height{vheight} {
      for (auto& row : grid) {
        row.reset();
      }
    }

    inline bit_matrix()
    : bit_matrix(0, 0) {

    }

    bit_matrix(bit_matrix const& o)
    : bit_matrix(o.height, o.width) {
      std::copy(std::begin(o.grid), std::end(o.grid), std::begin(grid));
    }

    bit_matrix(bit_matrix &&) = default;
    bit_matrix& operator=(bit_matrix const&) = default;
    bit_matrix& operator=(bit_matrix &&) = default;

    inline int
    count() const {
      auto rng = grid
        | std::views::drop(base_y)
        | std::views::take(height)
        | std::views::transform(&std::bitset<W>::count)
        | std::views::common;
      return std::accumulate(std::ranges::begin(rng), std::ranges::end(rng), 0u);
    }

    inline void resize(int vheight, int vwidth) {
      base_x = (W - vwidth) / 2;
      base_y = (H - vheight) / 2;
      width = vwidth;
      height = vheight;
    }

    inline void grow() {
      base_x -= 1;
      base_y -= 1;
      width += 2;
      height += 2;
    }

    inline int get_width() const {
      return width;
    }

    inline int get_height() const {
      return height;
    }

    inline bool in_bounds(int y, int x) const {
      return 0 <= y and y < static_cast<int>(height) and 0 <= x and x < static_cast<int>(width);
    }

    inline bool get(int dy, int dx, bool default_val) const {
      return in_bounds(dy, dx) ? grid[base_y + dy][base_x + dx] : default_val;
    }

    inline void set(int dy, int dx, bool value) {
      grid[base_y + dy].set(base_x + dx, value);
    }

  private:
    int base_x, base_y, width, height;
    std::array<std::bitset<W>, H> grid;
  };

  struct data {
    std::bitset<512> alg;
    bit_matrix<200, 200> init;
  };

  constexpr const int id = 20;
  using parsed = data;

  template <bool part2>
  using answer = int;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
