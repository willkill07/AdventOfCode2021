#pragma once

#include <vector>
#include <string>

#include <scn/all.h>

namespace day02 {
  enum class dir {
    up,
    down,
    forward
  };

  struct data {
    dir d;
    int amount;

    template <typename Context>
    scn::error
    scan(Context& ctx) {
      std::string dir;
      auto r = scn::scan(ctx.range(), "{} {}", dir, amount);
      d = [] (char c) {
        using day02::dir;
        switch (c) {
          case 'u': return dir::up;
          case 'd': return dir::down;
          default:  return dir::forward;
        }
      } (dir[0]);
      ctx.range() = std::move(r.range());
      return r.error();
    }
  };
  
  constexpr const int id = 2;
  using parsed = std::vector<data>;
  using result1 = int;
  using result2 = int;
}
