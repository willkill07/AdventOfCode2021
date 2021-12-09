#pragma once

#include <algorithm>
#include <array>
#include <tuple>

namespace day06 {

  constexpr const int id = 6;
  using parsed = std::array<unsigned long long, 9>;

  template <bool part2>
  using answer = unsigned long long;
  using result1 = answer<false>;
  using result2 = answer<true>;

  using number_t = unsigned long long;

  template <unsigned N, unsigned M>
  using matrix = std::array<std::array<number_t, M>, N>;

  template <unsigned N>
  using array = std::array<number_t, N>;

  template <typename T>
  concept is_array = requires {
    typename std::decay_t<T>::value_type;
    typename std::tuple_size<std::decay_t<T>>;
  };

  template <typename T>
  concept is_matrix = is_array<std::decay_t<T>> and is_array<typename std::decay_t<T>::value_type>;
  
  template <typename T>
  concept is_square_matrix = is_matrix<T> and (std::tuple_size_v<std::decay_t<T>> == std::tuple_size_v<typename std::decay_t<T>::value_type>);

  template <typename Lhs, typename Rhs>
  concept multiplicable =
    (is_matrix<Lhs> and is_matrix<Rhs> and (std::tuple_size_v<typename std::decay_t<Lhs>::value_type> == std::tuple_size_v<std::decay_t<Rhs>>)) or
    (is_matrix<Lhs> and is_array<Rhs>  and (std::tuple_size_v<typename std::decay_t<Lhs>::value_type> == std::tuple_size_v<std::decay_t<Rhs>>)) or
    (is_array<Lhs>  and is_matrix<Rhs> and (std::tuple_size_v<std::decay_t<Lhs>> == std::tuple_size_v<typename std::decay_t<Rhs>::value_type>));

  template <is_matrix Mat1, is_matrix Mat2>
  consteval auto
  operator*(Mat1&& a, Mat2&& b) requires multiplicable<Mat1, Mat2>{
    constexpr auto M = std::tuple_size_v<std::decay_t<Mat1>>;
    constexpr auto N = std::tuple_size_v<std::decay_t<Mat2>>;
    constexpr auto P = std::tuple_size_v<typename std::decay_t<Mat2>::value_type>;
    matrix<M, P> c;
    std::ranges::fill(c[0], 0);
    std::ranges::fill(c, c[0]);
    for (unsigned i{0}; i < M; ++i) {
      for (unsigned k{0}; k < N; ++k) {
        for (unsigned j{0}; j < P; ++j) {
          c[i][j] += a[i][k] * b[k][j];
        }
      }
    }
    return c;
  }

  template <is_square_matrix Mat>
  consteval std::decay_t<Mat>
  mpow(Mat&& mat, unsigned const N) {
    if (N & 1) {
      if (N > 1) {
        return mat * mpow(mat, (N - 1));
      } else {
        return mat;
      }
    } else {
      return mpow(mat * mat, N / 2);
    }
  }
}
