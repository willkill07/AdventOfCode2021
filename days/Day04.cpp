#include <algorithm>
#include <cctype>
#include <numeric>
#include <optional>
#include <ranges>
#include <vector>
#include <unordered_set>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day04.hpp"

namespace detail {
  using namespace day04;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

using day04::board_type;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  day04::data result;
  result.nums.reserve(100);
  result.boards.reserve(100);

  auto i = file.begin();
  for (; *i != '\n'; ++i) {
    int num{0};
    for (; std::isdigit(*i); ++i) {
      num = 10 * num + (*i - '0');
    }
    result.nums.push_back(num);
  }
  for (; not std::isdigit(*i); ++i) ;
  while(i < file.end()) {
    board_type b;
    for (unsigned long k{0}; k < 5ul; ++k) {
      for (unsigned long j{0}; j < 5ul; ++j) {
        int num{0};
        for (; std::isspace(*i); ++i) ;
        for (; std::isdigit(*i); ++i) {
          num = 10 * num + (*i - '0');
        }
        b[k][j] = num;
      }
    }
    result.boards.push_back(b);
    for (; not std::isdigit(*i); ++i) ;
  }
  return result;
}

inline int
score(board_type const& b) {
  auto vals = std::ranges::join_view(b) | std::ranges::views::filter([] (int v) { return v > 0; });
  return std::accumulate(std::ranges::begin(vals), std::ranges::end(vals), 0);
}

inline bool
has_won(board_type& b, unsigned r, unsigned c) {
  return ((b[r][0] < 0) and (b[r][1] < 0) and (b[r][2] < 0) and (b[r][3] < 0) and (b[r][4] < 0))
      or ((b[0][c] < 0) and (b[1][c] < 0) and (b[2][c] < 0) and (b[3][c] < 0) and (b[4][c] < 0));
}

template <bool solve_part2>
std::optional<int>
check_board(std::vector<board_type>& boards, unsigned bix, int num, std::unordered_set<unsigned>& won) {
  auto& b = boards[bix];
  for (unsigned r{0}; r < 5u; ++r) {
    for (unsigned c{0}; c < 5u; ++c) {
      if (num == b[r][c]) {
        b[r][c] += 0xdeadbeef; // make a sufficiently small negative number
        if (has_won(b, r, c)) {
          if constexpr (!solve_part2) {
            return score(b) * num;
          } else {
            won.insert(bix);
            return (std::size(won) == std::size(boards)) ? std::make_optional(score(b) * num) : std::nullopt;
          }
        }
      }
    }
  }
  return {};
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  // important: need to make a copy (to make it mutable)
  auto boards = data.boards;
  std::unordered_set<unsigned> won;
  for (int const num : data.nums) {
    for (unsigned bix{0}; bix < std::size(boards); ++bix) {
      if (not won.contains(bix)) {
        if (auto res = check_board<solve_part2>(boards, bix, num, won); res.has_value()) {
          return res.value();
        }
      }
    }
  }
  return 0;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
