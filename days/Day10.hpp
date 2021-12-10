#pragma once

#include <array>
#include <string>
#include <vector>

namespace day10 {

  constexpr const int id = 10;
  using parsed = std::vector<std::string>;

  template <bool part2>
  using answer = unsigned long;
  using result1 = answer<false>;
  using result2 = answer<true>;

consteval auto
illegal_values() {
  std::array<int, 8> result;
  result.fill(0);
  result[')' >> 4] = 3;
  result[']' >> 4] = 57;
  result['}' >> 4] = 1197;
  result['>' >> 4] = 25137;
  return result;
}

consteval auto
scores() {
  std::array<int, 8> result;
  result.fill(0);
  result[')' >> 4] = 1;
  result[']' >> 4] = 2;
  result['}' >> 4] = 3;
  result['>' >> 4] = 4;
  return result;
}

consteval auto
matches() {
  std::array<char, 8> result;
  result.fill(0);
  result[')' >> 4] = '(';
  result[']' >> 4] = '[';
  result['}' >> 4] = '{';
  result['>' >> 4] = '<';
  return result;
}

}
