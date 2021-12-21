#include <iterator>
#include <numeric>
#include <ranges>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day18.hpp"

namespace detail {
  using namespace day18;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

day18::SnailNumber
extract(auto iter, auto end) {
  day18::SnailNumber o;
  o.reserve(50);
  int level{0};
  for (auto i = iter; i != end; ++i) {
    char c = *i;
    if (c == '[') {
      level++;
    } else if (c == ']') {
      level--;
    } else if (c != ',') {
      o.push_back({c - '0', level});
    }
  }
  return o;
}

namespace {

bool
explode(day18::SnailNumber& p){
  auto end_minus_one = std::prev(std::end(p));
  for(auto it = std::begin(p); it != end_minus_one; ++it){
    auto n = std::next(it);
    auto [v1, d1] = *it;
    if(d1 > 4 && d1 == n->second){
      if (it != std::begin(p)) {
        std::prev(it)->first += v1;
      }
      auto [v2, d2] = *n;
      if (auto nn = std::next(n); nn != std::end(p)) {
        nn->first += v2;
      }
      it = p.erase(it);
      *it = { 0, d2 - 1 };
      return true;
    }
  }
  return false;
}

bool
split(day18::SnailNumber& p){
  for(auto it = std::begin(p); it != std::end(p); ++it){
    if (auto& [v, d] = *it; v >= 10) {
      int const half = v / 2;
      ++d;
      v -= half;
      p.insert(it, { half, d });
      return true;
    }
  }
  return false;
}

day18::SnailNumber
reduce(day18::SnailNumber& p) {
  while (true) {
    if (not explode(p) and not split(p)) {
      break;
    }
  }
  return p;
}

day18::SnailNumber
add(day18::SnailNumber a, day18::SnailNumber const& b){
  a.reserve(std::size(a) + std::size(b));
  a.insert(std::end(a), std::begin(b), std::end(b));
  for(auto& [k, v]: a) {
    v++;
  }
  return reduce(a);
}

int
magnitude (day18::SnailNumber l) {
  while (std::next(std::begin(l)) != std::end(l)) {
    for (auto it = std::begin(l); std::next(it) != std::end(l); ++it){
      auto& [v1, d1] = *it;
      auto n = std::next(it);
      auto [v2, d2] = *n;
      if (d1 == d2){
        v1 = 3 * v1 + 2 * v2;
        --d1;
        l.erase(n);
        break;
      }
    }
  }
  return std::begin(l)->first;
}

} // end anonymous namespace

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  Day::parsed_type result;
  result.reserve(100);
  for (auto iter = std::begin(file); iter < std::end(file); ) {
    auto end = std::find(iter, std::end(file), '\n');
    result.push_back(extract(iter, end));
    iter = std::next(end);
  }
  return result;
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {

  if constexpr (solve_part2) {
    int max{std::numeric_limits<int>::min()};
    #pragma omp parallel for reduction(max:max)
    for (unsigned i = 0u; i < std::size(data); ++i) {
      for (unsigned j = 0u; j < std::size(data); ++j) {
        if (i != j) {
          max = std::max({max, magnitude(add(data[i], data[j]))});
        }
      }
    }
    return max;
  } else {
    auto first = data.front();
    auto rest = data | std::views::drop(1) | std::views::common;
    return magnitude(std::accumulate(std::ranges::begin(rest), std::ranges::end(rest), first, add));
  }

}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
