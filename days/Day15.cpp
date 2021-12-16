#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day15.hpp"

namespace detail {
  using namespace day15;
  using Day = AdventDay<id, parsed, result1, result2>;

}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  
  scn::basic_mapped_file<char> file{filename.c_str()};
  day15::grid result;

  auto const HxWp1 = std::size(file) + 1;
  auto const W   = std::distance(std::begin(file), std::find(std::begin(file), std::end(file), '\n'));
  auto const H     = HxWp1 / (W + 1);

  result.data.assign(W * H, 0);
  result.w = static_cast<std::uint32_t>(W);
  result.h = static_cast<std::uint32_t>(H);

  auto iter = std::begin(file);
  auto out = std::begin(result.data);
  for (unsigned r{0}; r < H; ++r) {
    out = std::transform(iter, iter + W, out, [](auto i) { return i - '0'; });
    iter += W + 1;
  }

  return result;
}

struct state_t {
  std::uint32_t risk;
  std::uint16_t y, x;
};

template <>
template <bool solve_part2> 
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  constexpr unsigned repetitions = solve_part2 ? 5 : 1;

  auto const width = data.width<repetitions>();
  auto const height = data.height<repetitions>();

  auto const target_x = width - 1;
  auto const target_y = height - 1;
  
  std::vector<std::uint8_t> seen(height * width, 0);
  std::vector<std::vector<state_t>> queues(10, std::vector<state_t>{});
  // reserve twice max manhattan distance for each
  for (auto& q : queues) {
    q.reserve((width + height) * 2);
  }

  // costs 0 to start at top left
  queues[0].push_back({0, 0, 0});
  while (true) {
    // iterate through queues where we are at most risk+9 away
    // model with std::vector with preallocation to make it as fast as possible
    for (auto& q : queues){
      while (not q.empty()) {
        auto [risk, y, x] = q.back();
        q.pop_back();
        if (x == target_x and y == target_y) {
          return risk;
        }
        if (not seen[y * width + x]) {
          seen[y * width + x] = 1;
          if (x > 0 and not seen[y * width + x - 1]) {
            auto const new_x = static_cast<std::uint16_t>(x - 1);
            auto const new_risk = risk + data.get<repetitions>(y, new_x);
            queues[new_risk % 10].push_back({new_risk, y, new_x});
          }
          if (x < width - 1 and not seen[y * width + x + 1]) {
            auto const new_x = static_cast<std::uint16_t>(x + 1);
            auto new_risk = risk + data.get<repetitions>(y, new_x);
            queues[new_risk % 10].push_back({new_risk, y, new_x});
          }
          if (y > 0 and not seen[(y - 1) * width + x]) {
            auto const new_y = static_cast<std::uint16_t>(y - 1);
            auto const new_risk = risk + data.get<repetitions>(new_y, x);
            queues[new_risk % 10].push_back({new_risk, new_y, x});
          }
          if (y < height - 1 and not seen[(y + 1) * width + x]) {
            auto const new_y = static_cast<std::uint16_t>(y + 1);
            auto const new_risk = risk + data.get<repetitions>(new_y, x);
            queues[new_risk % 10].push_back({new_risk, new_y, x});
          }
        }
      }
    }
  }

  return 0;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
