#pragma once

#include <bitset>
#include <list>
#include <string>

#include <scn/all.h>

namespace day03 {

  struct data {
    using type = std::bitset<32>;

    type data;
    
    template <typename Context>
    scn::error
    scan(Context& ctx) {
      std::string line;
      auto r = scn::scan(ctx.range(), "{}", line);
      data = type {std::string {line.rbegin(), line.rend()}};
      ctx.range() = std::move(r.range());
      return r.error();
    }
  };

  constexpr const int id = 3;
  using parsed = std::list<data>;
  using result1 = int;
  using result2 = int;
}
