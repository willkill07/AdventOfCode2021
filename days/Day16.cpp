#include <algorithm>
#include <limits>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day16.hpp"

namespace detail {
  using namespace day16;
  using Day = AdventDay<id, parsed, result1, result2>;

}
using detail::Day;

namespace {

template <unsigned N>
std::int64_t
extract(auto& i) {
  auto j = std::exchange(i, std::next(i, N));
  return [j] <unsigned ...I> (std::integer_sequence<unsigned, I...>) {
    return ((static_cast<std::int64_t>(*std::ranges::next(j, I)) << (N - 1 - I)) | ...);
  }(std::make_integer_sequence<unsigned, N>{});
}

template <typename Iter>
std::pair<day16::Node, Iter>
recursive_parse(Iter i) {
  auto const version = static_cast<std::uint8_t>(extract<3>(i));
  if (auto const type = static_cast<std::uint8_t>(extract<3>(i)); type == 4) {
    // Literal
    std::int64_t value{0};
    while (extract<1>(i) == 1) {
      value = (value << 4) | extract<4>(i);
    }
    value = (value << 4) | extract<4>(i);
    return { day16::Literal{ version, value }, i };
  } else {
    // Operator
    day16::Operator op { version, type, {} };
    if (auto const length_id = extract<1>(i); length_id == 0) {
      auto const bits = extract<15>(i);
      auto const target = std::next(i, bits);
      while (i != target) {
        auto [subpacket, i_next] = recursive_parse(i);
        op.operands.push_back(std::move(subpacket));
        i = i_next;
      }
    } else {
      auto const packets = extract<11>(i);
      for (unsigned p{0}; p < packets; ++p) {
        auto [subpacket, i_next] = recursive_parse(i);
        op.operands.push_back(std::move(subpacket));
        i = i_next;
      }
    }
    return { op, i };
  }
}

}

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  
  scn::basic_mapped_file<char> file{filename.c_str()};
  auto rng = file
    | std::views::transform ([] (char c) {
        // map the character to a hex value [0, 16)
        auto const val = static_cast<std::uint8_t>(c - (std::isdigit(c) ?  '0' : ('A' - 10)));
        // each hex digit is four bits, so map to an array
        return std::array { (val & 0b1000) >> 3, (val & 0b0100) >> 2, (val & 0b0010) >> 1, val & 0b0001 };
      })
      // join the arrays together as one range
    | std::views::join
      // get a common iterator that can be used with non-range stuff
    | std::views::common;

  // map the range to a single vector of bits
  auto bits = std::vector<std::uint8_t>(std::ranges::begin(rng), std::ranges::end(rng));
  
  // parse away!
  auto [result, _] = recursive_parse(std::ranges::begin(bits));
  return result;
}

template <>
template <bool solve_part2> 
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {
  if constexpr (solve_part2) {
    return std::visit(day16::Evaluator{}, data);
  } else {
    return std::visit(day16::VersionAdder{}, data);
  }
  return 0;
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
