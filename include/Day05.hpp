#pragma once

#include <array>
#include <vector>
#include <string>

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

    template <typename Context>
    scn::error
    scan(Context& ctx) {
      auto r = scn::scan(ctx.range(), "{},{} -> {},{}", src.x, src.y, dst.x, dst.y);
      ctx.range() = std::move(r.range());
      return r.error();
    }
  };

  constexpr const int id = 5;
  using parsed = std::vector<edge>;
  using result1 = int;
  using result2 = int;
}
