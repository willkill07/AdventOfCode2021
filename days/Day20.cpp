#include <iterator>
#include <numeric>
#include <ranges>

#include <scn/all.h>

#include "AdventDay.hpp"
#include "Day20.hpp"

namespace detail {
  using namespace day20;
  using Day = AdventDay<id, parsed, result1, result2>;
}
using detail::Day;

template <>
Day::parsed_type
Day::parse(std::string const& filename) {
  scn::basic_mapped_file<char> file{filename.c_str()};
  Day::parsed_type result;
  for (unsigned i{0}; i < 512; ++i) {
    result.alg.set(i, std::begin(file)[i] != '.');
  }
  auto first = std::begin(file) + 512 + 1 + 1;
  auto const width = static_cast<int>(std::distance(first, std::find(first, std::end(file), '\n')));
  auto const height = static_cast<int>(std::distance(first, std::end(file)) + 1) / (width + 1);

  result.init.resize(height, width);

  for (int i{0}; i < height; ++i) {
    for (int j{0}; j < width; ++j) {
      result.init.set(i, j, *first != '.');
      ++first;
    }
    ++first;
  }
  return result;
}

template <>
template <bool solve_part2>
Day::answer<solve_part2>
Day::solve(Day::parsed_type const& data, Day::opt_answer) {

  day20::bit_matrix<200, 200> mat {data.init}, new_mat {mat};
  new_mat.grow();
  bool repeat = false;

  auto step = [&] {
    #pragma omp for
    for (int y = 0; y < new_mat.get_height(); ++y) {
      for (int x = 0; x < new_mat.get_width(); ++x) {
        int const val =
          (mat.get(y - 2, x - 2, repeat) << 8) | (mat.get(y - 2, x - 1, repeat) << 7) | (mat.get(y - 2, x - 0, repeat) << 6) |
          (mat.get(y - 1, x - 2, repeat) << 5) | (mat.get(y - 1, x - 1, repeat) << 4) | (mat.get(y - 1, x - 0, repeat) << 3) |
          (mat.get(y - 0, x - 2, repeat) << 2) | (mat.get(y - 0, x - 1, repeat) << 1) | (mat.get(y - 0, x - 0, repeat) << 0);
        new_mat.set(y, x, data.alg[val]);
      }
    }
    #pragma omp barrier
    #pragma omp master
    {
      mat = new_mat;
      repeat ^= data.alg[0];
      new_mat.grow();
    }
    #pragma omp barrier
  };

  #pragma omp parallel
  {
    for (int i = 0; i < (solve_part2 ? 50 : 2); i++) {
      step();
    }
  }

  return mat.count();
}

INSTANTIATE(Day, true);
INSTANTIATE(Day, false);
