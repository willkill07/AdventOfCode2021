#include <algorithm>
#include <cctype>
#include <limits>
#include <map>
#include <numeric>
#include <ranges>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day12.hpp"

namespace detail {
  using namespace day12;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

day12::graph::graph(std::vector<std::pair<std::string_view, std::string_view>> const& es) {

  std::uint8_t small_count{2};
  std::uint8_t large_count{0};
  std::unordered_map<std::string_view, std::uint8_t> lookup;
  lookup["start"] = 0;
  lookup["end"] = 1;

  auto get_id = [&] (std::string_view s) {
    std::uint8_t id;
    if (auto i = lookup.find(s); i != lookup.end()) {
      id = i->second;
    } else {
      if (std::isupper(s[0])) {
        id = static_cast<std::uint8_t>(-(++large_count));
      } else {
        id = small_count++;
      }
      lookup[s] = id;
    }
    return id;
  };

  // transform strings into integers; make adjacency matrix
  auto const adj = [&] {
    std::map<std::uint8_t, std::set<std::uint8_t>> a;
    for (auto&& [u, v] : es) {
      auto const uid = get_id(u);
      auto const vid = get_id(v);
      a[uid].insert(vid);
      a[vid].insert(uid);
    }
    return a;
  }();

  std::vector<std::uint8_t> adjmat (small_count * small_count, 0);
  for (auto&& [u, alist] : adj) {
    if (u < 128) {
      for (auto&& v : alist) {
        if (v < 128 and u != end and v != start) {
          ++adjmat[u * small_count + v];
        }
      }
    } else {
      for (auto&& v : alist) {
        for (auto&& w : alist) {
          if (v != w) {
            if (v != end and w != start) {
              ++adjmat[v * small_count + w];
            }
          }
        }
      }
    }
  }

  data.reserve(small_count * small_count);
  edges.resize(small_count);

  std::uint8_t k{0};
  auto iter = std::begin(data);
  for (std::uint8_t i{0}; i < small_count; ++i) {
    auto curr_start = iter;
    for (std::uint8_t j{0}; j < small_count; ++j) {
      if (adjmat[k] != 0) {
        data.push_back({j, adjmat[k]});
        ++iter;
      }
      ++k;
    }
    edges[i] = std::span{curr_start, iter};
  }
}

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  std::vector<std::pair<std::string_view,std::string_view>> edges;
  for (auto i = std::begin(file); i < std::end(file); ++i) {
    while (not std::isalpha(*i)) { ++i; }
    auto begin1 = i;
    while (std::isalpha(*i)) { ++i; }
    auto end1 = i;
    while (not std::isalpha(*i)) { ++i; }
    auto begin2 = i;
    while (std::isalpha(*i)) { ++i; }
    auto end2 = i;
    edges.push_back({std::string_view{begin1, end1}, std::string_view{begin2, end2}});
  }

  return day12::graph{edges};
}


constexpr auto const start_cave = day12::graph::start;
constexpr auto const end_cave = day12::graph::end;

int depth{0};

template <bool Twice>
unsigned
discover(unsigned from, std::vector<std::uint8_t>& visit_count, auto const& edges) {
  unsigned total_paths{0};
  for (auto&& [to, num_paths] : edges[from]) {
    if (to == start_cave) {
      continue;
    }
    if (to == end_cave) {
      total_paths += num_paths;
      continue;
    }
    if (++visit_count[to] == 1) {
      total_paths += num_paths * discover<Twice>(to, visit_count, edges);
    } else if constexpr (not Twice) {
      if (visit_count[to] == 2) {
        total_paths += num_paths * discover<true>(to, visit_count, edges);
      }
    }
    --visit_count[to];
  }
  return total_paths;
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  std::vector<std::uint8_t> visit_count(std::size(data.edges), 0);
  return discover<(not solve_part2)>(start_cave, visit_count, data.edges);
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
