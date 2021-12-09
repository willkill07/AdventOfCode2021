#pragma once

#include <vector>

#include <scn/all.h>

namespace day05 {

  struct point {
    int x, y;
    
    constexpr inline point& operator+=(point const& p) noexcept { x += p.x; y += p.y; return *this; }
    constexpr inline point& operator-=(point const& p) noexcept { x -= p.x; y -= p.y; return *this; }
    constexpr inline point operator+(point const& p) const noexcept { point n{*this}; return n += p; }
    constexpr inline point operator-(point const& p) const noexcept { point n{*this}; return n -= p; }
    constexpr inline bool diagonal() const noexcept { return x == y or x == -y; }
    constexpr inline bool straight() const noexcept{ return x == 0 or y == 0; }
    constexpr inline bool single() const noexcept { return x == 0 and y == 0; }
    constexpr inline auto operator<=>(point const&) const = default;
  };

  struct edge {
    point src, dst;
    constexpr inline auto operator<=>(edge const&) const = default;
  };

  constexpr const int id = 5;
  using parsed = std::vector<edge>;

  template <bool part2>
  using answer = int;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
