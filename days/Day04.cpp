#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>
#include <unordered_set>

#include "AdventDays.hpp"
#include "Day04.hpp"

using Day = get_day<4>;

using parsed_type = typename Day::parsed_type;
using part1_opt = std::optional<typename Day::answer_one_type>;

template <bool part2>
using answer = std::conditional_t<part2, typename Day::answer_two_type, typename Day::answer_one_type>;

using board_type = day04::data::board_type;

template <>
parsed_type
Day::parse(char const* filename) {
  scn::basic_mapped_file<char> file{filename};
  day04::data result;
  auto r = scn::scan_list_until(file, result.nums, '\n', ',').range();
  scn::ignore_until(r, '\n');
  scn::ignore_until(r, '\n');
  while (!r.empty()) {
    board_type b;
    for (unsigned long i{0}; i < 5ul; ++i) {
      auto res = scn::scan(r, "{} {} {} {} {}\n", b[i][0], b[i][1], b[i][2], b[i][3], b[i][4]);
      r = res.range();
      scn::ignore_until(r, '\n');
    }
    result.boards.push_back(b);
    scn::ignore_until(r, '\n');
  }
  return result;
}

inline int
score(board_type const& b) {
  auto vals = std::ranges::join_view(b) | std::ranges::views::filter([] (int v) { return v > 0; });
  return std::accumulate(vals.begin(), vals.end(), 0);
}

inline bool
has_won(board_type& b, unsigned r, unsigned c) {
  bool hor{true}, ver{true};
  for (std::size_t i{0}; i < 5; ++i) {
    hor &= (b[r][i] < 0);
    ver &= (b[i][c] < 0);
  }
  return (hor or ver);
}

template <bool solve_part2>
std::optional<int>
check_board(std::vector<board_type>& boards, unsigned bix, int num, std::unordered_set<unsigned>& won) {
  auto& b = boards[bix];
  for (unsigned r{0}; r < 5u; ++r) {
    for (unsigned c{0}; c < 5u; ++c) {
      if (num == b[r][c]) {
        b[r][c] = b[r][c] - 0xFFFF;
        if (has_won(b, r, c)) {
          if constexpr (!solve_part2) {
            return score(b) * num;
          } else {
            won.insert(bix);
            if (std::size(won) == std::size(boards)) {
              return score(b) * num;
            } else {
              return {};
            }
          }
        }
      }
    }
  }
  return {};
}

template <>
template <bool solve_part2>
answer<solve_part2>
Day::solve(parsed_type const& data, part1_opt) {
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
