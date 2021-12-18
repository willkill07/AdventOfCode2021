#include <numeric>
#include <ranges>
#include <variant>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day18.hpp"

namespace detail {
  using namespace day18;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

template <typename Iter>
std::pair<Iter, day18::SnailNumber>
recursive_parse(Iter iter) {    
  if (char const c = *iter++; c == '[') {
    auto [i, lhs] = recursive_parse(iter);
    ++i; // skip ,
    auto [j, rhs] = recursive_parse(i);
    ++j; // skip ]
    return { j, new day18::Snail{lhs, rhs} };
  } else {
    return { iter, int{c - '0'} };
  }
}

namespace {

struct Printer {
  void
  operator()(day18::Snail* s) const {
    fmt::print("[");
    std::visit(*this, s->left);
    fmt::print(",");
    std::visit(*this, s->right);
    fmt::print("]");
  }
  void
  operator()(int v) const {
    fmt::print("{}", v);
  }

  ~Printer() {
    fmt::print("\n");
  }
};

struct Splitter {

  std::pair<bool, day18::SnailNumber> 
  operator()(day18::Snail* s) const {
    if (auto [did_split_lhs, lhs] = std::visit(*this, s->left); did_split_lhs) {
      s->left = lhs;
      return { true, s };
    } else if (auto [did_split_rhs, rhs] = std::visit(*this, s->right); did_split_rhs) {
      s->right = rhs;
      return { true, s };
    } else {
      return { false, s };
    }
  }

  std::pair<bool, day18::SnailNumber>
  operator()(int v) const {
    if (v >= 10) {
      return { true, new day18::Snail{v / 2, (v + 1) / 2} };
    } else {
      return { false, v };
    }
  }
};

struct Exploder {

  void reset() {
    level = 0;
  }

  std::tuple<bool, day18::SnailNumber, int, int>
  operator()(day18::Snail* s) {
    if (level < 4) {
      ++level;
      if (auto [exploded_left, new_left, left_val1, right_val1] = std::visit(*this, s->left); exploded_left) {
        --level;
        s->left = new_left;
        s->right = add_to_left(s->right, right_val1);
        return { true, s, left_val1, 0 };
      } else if (auto [exploded_right, new_right, left_val2, right_val2] = std::visit(*this, s->right); exploded_right) {
        --level;
        s->right = new_right;
        s->left = add_to_right(s->left, left_val2);
        return { true, s , 0, right_val2 };
      } else {
        --level;
        return { false, s, 0, 0 };
      }
    } else {
      return { true, 0, std::get<int>(s->left), std::get<int>(s->right) };
    }
  }

  std::tuple<bool, day18::SnailNumber, int, int>
  operator()(int& v) {
    return { false, v, 0, 0 };
  }

private:
  int level{0};

  day18::SnailNumber
  add_to_left(day18::SnailNumber& num, int const num_to_add) const {
    if (std::holds_alternative<int>(num)) {
      return { std::get<int>(num) + num_to_add };
    } else {
      auto* n = std::get<day18::Snail*>(num);
      n->left = add_to_left(n->left, num_to_add);
      return num;
    }
  }

  day18::SnailNumber
  add_to_right(day18::SnailNumber& num, int const num_to_add) const {
    if (std::holds_alternative<int>(num)) {
      return std::get<int>(num) + num_to_add;
    } else {
      auto* n = std::get<day18::Snail*>(num);
      n->right = add_to_right(n->right, num_to_add);
      return num;
    }
  }
};

struct Magnitude {

  int
  operator()(day18::Snail* s) const {
    return std::visit(*this, s->left) * 3 + std::visit(*this, s->right) * 2;
  }

  int
  operator()(int v) const {
    return v;
  }
};

day18::SnailNumber
reduce (day18::SnailNumber n) {
  day18::Copier c;
  Exploder e;
  Splitter s;
  n = std::visit(c, n);
  while (true) {
    e.reset();
    auto [exploded, num, l, r] = std::visit(e, n);
    if (not exploded) {
      auto [splitted, new_num] = std::visit(s, num);
      if (not splitted) {
        return num;
      }
      n = new_num;
    }
  }
}

day18::SnailNumber
add (day18::SnailNumber a, day18::SnailNumber b) {
  return reduce(new day18::Snail { a, b });
}

} // end anonymous namespace

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  Day::parsed_type result;
  result.nums.reserve(100);
  for (auto iter = std::begin(file); iter < std::end(file); ) {
    auto [new_iter, snail] = recursive_parse(iter);
    iter = new_iter + 1;
    result.nums.push_back(snail);
  }
  return result;
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {

  if constexpr(solve_part2) {
    int max{std::numeric_limits<int>::min()};
    for (unsigned i{0}; auto& a : data.nums) {
      for (unsigned j{0}; auto& b : data.nums) {
        if (i != j) {
          auto c = add(a, b);
          max = std::max({max, std::visit(Magnitude{}, c)});
          //std::visit(day18::Deleter{}, c);
        }
        ++j;
      }
      ++i;
    }
    return max;
  } else {
    auto all_but_first = data.nums | std::views::drop(1) | std::views::common;
    auto first = data.nums.front();
    auto result = std::accumulate(std::ranges::begin(all_but_first), std::ranges::end(all_but_first), first, add);
    int magnitude = std::visit(Magnitude{}, result);
    std::visit(day18::Deleter{}, result);
    return magnitude;
  }

  return 0;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
