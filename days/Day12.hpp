#pragma once

#include <span>
#include <string_view>
#include <vector>
#include <utility>

namespace day12 {

  struct graph {

    static constexpr const std::int8_t start{0}, end{1};

    graph(std::vector<std::pair<std::string_view, std::string_view>> const&);
    graph() = default;
    ~graph() = default;
    graph(graph const&) = default;
    graph(graph &&) = default;
    graph& operator=(graph const&) = default;
    graph& operator=(graph &&) = default;

    std::vector<std::span<std::pair<std::uint8_t,std::uint8_t>>> edges;
  private:
    std::vector<std::pair<std::uint8_t,std::uint8_t>> data;
  };

  constexpr const int id = 12;
  using parsed = graph;

  template <bool part2>
  using answer = unsigned;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
