#pragma once

#include <array>
#include <utility>
#include <vector>

namespace day22 {

  struct point {
    int x, y, z;
    inline constexpr point& operator-=(point const& o) noexcept {
      x -= o.x; y -= o.y; z -= o.z; return *this;
    }
    inline constexpr point& operator+=(point const& o) noexcept {
      x += o.x; y += o.y; z += o.z; return *this;
    }
    inline constexpr point operator+(point const& o) const noexcept {
      point copy{*this}; copy += o; return copy;
    }
    inline constexpr point operator-(point const& o) const noexcept {
      point copy{*this}; copy -= o; return copy;
    }
    inline constexpr static point max(point const& a, point const& b) noexcept {
      return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z) };
    }
    inline constexpr static point min(point const& a, point const& b) noexcept {
      return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z) };
    }
  };

  struct box {
    point lo, hi;

    inline constexpr bool intersects(box const& o) const {
      if (hi.x < o.lo.x or o.hi.x < lo.x) return false;
      if (hi.y < o.lo.y or o.hi.y < lo.y) return false;
      if (hi.z < o.lo.z or o.hi.z < lo.z) return false;
      return true;
    }

    inline constexpr static
    void
    difference(box const& a, box const& b, std::vector<box>& to_add) {
      box const c { point::max(a.lo, b.lo), point::min(a.hi, b.hi) };
      if (a.lo.z < c.lo.z) to_add.push_back({ {a.lo.x,     a.lo.y,     a.lo.z},     {a.hi.x,     a.hi.y,     c.lo.z - 1} });
      if (c.hi.z < a.hi.z) to_add.push_back({ {a.lo.x,     a.lo.y,     c.hi.z + 1}, {a.hi.x,     a.hi.y,     a.hi.z} });
      if (a.lo.x < c.lo.x) to_add.push_back({ {a.lo.x,     a.lo.y,     c.lo.z},     {c.lo.x - 1, a.hi.y,     c.hi.z} });
      if (c.hi.x < a.hi.x) to_add.push_back({ {c.hi.x + 1, a.lo.y,     c.lo.z},     {a.hi.x,     a.hi.y,     c.hi.z} });
	    if (a.lo.y < c.lo.y) to_add.push_back({ {c.lo.x,     a.lo.y,     c.lo.z},     {c.hi.x,     c.lo.y - 1, c.hi.z} });
	    if (c.hi.y < a.hi.y) to_add.push_back({ {c.lo.x,     c.hi.y + 1, c.lo.z},     {c.hi.x,     a.hi.y,     c.hi.z} });
    }
  };

  constexpr const int id = 22;
  using parsed = std::vector<std::pair<bool, box>>;

  template <bool part2>
  using answer = unsigned long;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
