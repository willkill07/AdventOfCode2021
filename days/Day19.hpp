#pragma once

#include <bit>
#include <compare>
#include <vector>


namespace day19 {
 
  struct beacon {
    int x, y, z;

    inline constexpr beacon(int x_, int y_, int z_)
    : x{x_}, y{y_}, z{z_} {}

    inline constexpr beacon()
    : beacon{0,0,0} {}

    constexpr auto
    operator<=>(beacon const& ) const = default;
    
    friend inline constexpr beacon
    operator+(beacon const& a, beacon const& b) {
      return beacon(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    friend inline constexpr beacon
    operator-(beacon const& a, beacon const& b) {
      return beacon(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    static inline constexpr int
    dist(beacon const& a, beacon const& b) {
      beacon const t = a - b;
      return t.x * t.x + t.y * t.y + t.z * t.z;
    }

    static inline constexpr int
    manhattan(beacon const& a, beacon const& b) {
      beacon t {a - b};
      return abs(t.x) + abs(t.y) + abs(t.z);
    }
  };

  using scanner = std::vector<beacon>;

  constexpr const int id = 19;
  using parsed = std::vector<scanner>;

  template <bool part2>
  using answer = int;
  using result1 = answer<false>;
  using result2 = answer<true>;
}

namespace std {

template <> struct hash<day19::beacon> {
  std::size_t operator()(day19::beacon const& p) const {
    return std::bit_cast<std::uint64_t>(static_cast<std::int64_t>(p.x)) << 32 ^
           std::bit_cast<std::uint64_t>(static_cast<std::int64_t>(p.y)) << 16 ^
           std::bit_cast<std::uint64_t>(static_cast<std::int64_t>(p.z));
  }
};

} // namespace std
