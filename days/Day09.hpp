#pragma once

#include <array>
#include <algorithm>
#include <ranges>
#include <span>
#include <vector>

namespace day09 {

  struct matrix {

    inline matrix() = default;

    inline matrix(std::span<char const> buffer)
    : m_data(new char[buffer.size() + 1])
    , m_size(static_cast<unsigned>(buffer.size() + 1))
    , m_width(static_cast<unsigned>(std::distance(std::begin(buffer), std::ranges::find(buffer, '\n'))))
    , m_height(m_size / (m_width + 1)) {
      std::ranges::copy(buffer, m_data);
    }

    inline matrix(matrix const& other)
    : m_data(new char[other.m_size])
    , m_size(other.m_size)
    , m_width(other.m_width)
    , m_height(other.m_height) {
      std::copy_n(other.m_data, other.m_size, m_data);
    }

    inline matrix& operator= (matrix const& other) {
      if (this != &other) {
        if (m_size < other.m_size) {
          delete[] std::exchange(m_data, new char[other.m_size]);
        }
        m_size = other.m_size;
        m_width = other.m_width;
        m_height = other.m_height;
        std::copy_n(other.m_data, other.m_size, m_data);
      }
      return *this;
    }

    inline char* begin() { return m_data; }
    inline char const* begin() const { return m_data; }
    inline char const* cbegin() const { return m_data; }
    inline char* end() { return m_data + m_size; }
    inline char const* end() const { return m_data; }
    inline char const* cend() const { return m_data; }
    inline unsigned size() const { return m_size; }
    inline unsigned width() const { return m_width; }
    inline unsigned height() const { return m_height; }
    inline char& operator()(unsigned r, unsigned c) { return m_data[r * (width() + 1) + c]; }
    inline char operator()(unsigned r, unsigned c) const { return m_data[r * (width() + 1) + c]; }
    inline std::span<char> operator[](unsigned r) { return std::span<char>(begin() + r * (width() + 1),  begin() + (r + 1) * (width() + 1) - 1); }
    inline std::span<const char> operator[](unsigned r) const { return std::span<char const>(begin() + r * (width() + 1),  begin() + (r + 1) * (width() + 1) - 1); }

    inline ~matrix() {
      delete[] m_data;
    }
  private:
    char* m_data{nullptr};
    unsigned m_size{0u};
    unsigned m_width{0u};
    unsigned m_height{0u};
  };

  constexpr const int id = 9;
  using parsed = matrix;

  template <bool part2>
  using answer = int;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
