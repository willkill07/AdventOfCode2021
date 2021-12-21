#include <algorithm>
#include <numeric>
#include <ranges>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day19.hpp"

namespace detail {
  using namespace day19;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

using day19::beacon;
using day19::scanner;

namespace {


inline std::vector<std::vector<int>>
make_fingerprints(std::vector<scanner> const& scns) {
  std::vector<std::vector<int>> fingerprints (std::size(scns));
  #pragma omp parallel for
  for (unsigned i = 0; i < std::size(fingerprints); ++i) {
    auto& s = scns[i];
    std::vector<int> curr;
    auto const N = std::size(s);
    curr.reserve((N - 2) * (N - 1) / 2);
    for (unsigned j = 0; j < N - 1; j++) {
      for (unsigned k = j + 1; k < N; k++) {
        curr.push_back(beacon::dist(s[j], s[k]));
      }
    }
    std::ranges::sort(curr);
    curr.resize(std::distance(std::begin(curr), std::unique(std::begin(curr), std::end(curr))));
    fingerprints[i] = std::move(curr);
  }
  return fingerprints;
}

inline int
is_adjacent(std::vector<int> const& a, std::vector<int> const& b, int limit) {
  auto first1 = std::begin(a); auto last1 = std::end(a);
  auto first2 = std::begin(b); auto last2 = std::end(b);
  int matched = 0;
  while (first1 != last1 && first2 != last2) {
    if (*first1 < *first2) {
      ++first1;
    } else  {
      if (!(*first2 < *first1)) {
        if (++matched == limit) {
          return true;
        }
        ++first1;
      }
      ++first2;
    }
  }
  return false;
}

inline std::pair<beacon, int>
max_value(std::unordered_map<beacon, int> const& m) {
  return *std::ranges::max_element(m, {}, &std::unordered_map<beacon, int>::value_type::second);
}

std::array const perms = {
  +[](beacon const& p) { return beacon{ p.x,  p.y,  p.z}; },
  +[](beacon const& p) { return beacon{ p.x, -p.z,  p.y}; },
  +[](beacon const& p) { return beacon{ p.x, -p.y, -p.z}; },
  +[](beacon const& p) { return beacon{ p.x,  p.z, -p.y}; },
  +[](beacon const& p) { return beacon{-p.y,  p.x,  p.z}; },
  +[](beacon const& p) { return beacon{ p.z,  p.x,  p.y}; },
  +[](beacon const& p) { return beacon{ p.y,  p.x, -p.z}; },
  +[](beacon const& p) { return beacon{-p.z,  p.x, -p.y}; },
  +[](beacon const& p) { return beacon{-p.x, -p.y,  p.z}; },
  +[](beacon const& p) { return beacon{-p.x, -p.z, -p.y}; },
  +[](beacon const& p) { return beacon{-p.x,  p.y, -p.z}; },
  +[](beacon const& p) { return beacon{-p.x,  p.z,  p.y}; },
  +[](beacon const& p) { return beacon{ p.y, -p.x,  p.z}; },
  +[](beacon const& p) { return beacon{ p.z, -p.x, -p.y}; },
  +[](beacon const& p) { return beacon{-p.y, -p.x, -p.z}; },
  +[](beacon const& p) { return beacon{-p.z, -p.x,  p.y}; },
  +[](beacon const& p) { return beacon{-p.z,  p.y,  p.x}; },
  +[](beacon const& p) { return beacon{ p.y,  p.z,  p.x}; },
  +[](beacon const& p) { return beacon{ p.z, -p.y,  p.x}; },
  +[](beacon const& p) { return beacon{-p.y, -p.z,  p.x}; },
  +[](beacon const& p) { return beacon{-p.z, -p.y, -p.x}; },
  +[](beacon const& p) { return beacon{-p.y,  p.z, -p.x}; },
  +[](beacon const& p) { return beacon{ p.z,  p.y, -p.x}; },
  +[](beacon const& p) { return beacon{ p.y, -p.z, -p.x}; }
};

} // anonymous namespace

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};

  auto get_num = [] (auto& i) {
    bool negate = (*i == '-');
    i += +negate;
    int num{0};
    while (::isdigit(*i)) {
      num = 10 * num + (*i - '0');
      ++i;
    }
    return negate ? -num : num;
  };

  Day::parsed_type result;
  result.reserve(38);

  auto it = std::find(std::begin(file), std::end(file), '\n');
  while (it < std::end(file)) {
    // skip header
    day19::scanner s;
    while (++it < std::end(file) and *it != '\n') {
      int x = get_num(it);
      ++it; // comma
      int y = get_num(it);
      ++it; // comma
      int z = get_num(it);
      s.push_back({x, y, z});
    }
    result.push_back(std::move(s));
    // skip newlines
    it += 2;
  }
  return result;
}

namespace {
  bool prepared = false;
  std::vector<int> done;
  std::vector<int> solved;
  std::vector<beacon> position;
  std::vector<std::vector<beacon>> beacons;
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  
  auto const fingerprints = make_fingerprints(data);

  if (not prepared) {
    prepared = true;
    done.assign(std::size(data), 0);
    solved.assign(std::size(data), 0);
    position.assign(std::size(data), {});
    beacons.assign(std::size(data), {});
    solved[0] = 1;
    beacons[0] = data[0];
      
    #pragma omp parallel
    {
      for (unsigned all_done{0}; all_done != std::size(data); ) {
        for (unsigned i = 0u; i < std::size(data); ++i) {
          if (solved[i] and not done[i]) {
            #pragma omp for schedule(dynamic, 1)
            for (unsigned j = 0u; j < std::size(data); ++j) {
              if (i != j and not solved[j]) {
                if (is_adjacent(fingerprints[i], fingerprints[j], 66)) {
                  for (unsigned p = 0u; p < std::size(perms); ++p) {
                    beacons[j].resize(std::size(data[j]));
                    std::ranges::transform(data[j], std::begin(beacons[j]), perms[p]);
                    auto const counter = [&] {
                      std::unordered_map<beacon, int> c;
                      for (auto&& en : beacons[i])
                        for (auto&& st : beacons[j])
                          c[en - st]++;
                      return c;
                    }();
                    if (auto [k, v] = max_value(counter); v >= 12) {
                      solved[j] = true;
                      position[j] = position[i] + k;
                      break;
                    }
                  }
                }
              }
            }
            done[i] = true;
            #pragma omp atomic update
            ++all_done;
          }
        }
      }
    }
  }
  
  if constexpr (solve_part2) {
    int max_dist = 0;
    for (auto&& p : position) {
      for (auto&& s : position) {
        max_dist = std::max({ max_dist, beacon::manhattan(p, s) });
      }
    }
    return max_dist;
  } else {
    std::unordered_set<beacon> unique(1000);
    for (unsigned i = 0u; i < std::size(data); ++i) {
      for (auto&& p : beacons[i]) {
        unique.insert(p + position[i]);
      }
    }
    prepared = false;
    return static_cast<int>(unique.size());
  }
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
