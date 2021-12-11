#include <algorithm>
#include <limits>
#include <numeric>
#include <ranges>
#include <vector>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day11.hpp"

namespace detail {
  using namespace day11;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  day11::board result;
  result[0].fill(std::numeric_limits<int>::min());
  result.fill(result[0]);
  auto iter = file.begin();
  for (unsigned row{1}; row <= 10; ++row) {
    for (unsigned col{1}; col <= 10; ++col) {
      result[row][col] = (*iter - '0');
      ++iter;
    }
    ++iter;
  }
  return result;
}

constexpr const int threshold = 9;

unsigned
step(day11::board& b) {
  static std::vector<std::pair<int, int>> queue;
  queue.reserve(100); // reserve enough for each point to be in the queue

  auto check_and_enqueue = [&] (int r, int c) {
    if (++b[r][c] > threshold) {
      b[r][c] = std::numeric_limits<int>::min();
      queue.push_back({r, c});
    }
  };

  auto try_get = [&] (int& y, int& x) {
    if (queue.empty()) {
      return false;
    } else {
      y = queue.back().first;
      x = queue.back().second;
      queue.pop_back();
      return true;
    }
  };

  for (int r{1}; r <= 10; ++r) {
    for (int c{1}; c <= 10; ++c) {
      check_and_enqueue(r, c);
    }
  }

  if (queue.size() != 100) {
    for (int y, x; try_get(y, x); ) {
      for (int const dy : {-1, 0 , 1}) {
        for (int const dx : {-1, 0, 1}) {
          if (dy != 0 or dx != 0) {
            check_and_enqueue(y + dy, x + dx);
          }
        }
      }
    }
  }
  
  unsigned flashes{0};
  for (int r{1}; r <= 10; ++r) {
    for (int c{1}; c <= 10; ++c) {
      if (b[r][c] < 0) {
        b[r][c] = 0;
        ++flashes;
      }
    }
  }
  return flashes;
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  day11::board board{data};
  unsigned total_flashes{0};
  unsigned time{1};
  while (true) {
    unsigned flashes = step(board); 
    if constexpr (solve_part2) {
      if (flashes == 100) {
        return time;
      }
    } else {
      total_flashes += flashes;
      if (time == 100) {
        return total_flashes;
      }
    }
    ++time;
  }
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
