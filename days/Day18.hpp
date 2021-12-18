#pragma once

#include <variant>
#include <vector>

namespace day18 {

  struct Snail;

  using SnailNumber = std::variant<Snail*, int>;

  struct Snail {
    SnailNumber left, right;
  };

  struct Copier {

    inline day18::SnailNumber
    operator()(day18::Snail* s) const {
      return new day18::Snail{ std::visit(*this, s->left), std::visit(*this, s->right) };
    }

    inline day18::SnailNumber
    operator()(int v) const {
      return v;
    }
  };

  struct Deleter {
    inline void
    operator()(day18::Snail* s) const {
      std::visit(*this, s->left);
      std::visit(*this, s->right);
      delete s;
    }

    inline void
    operator()(int) const {
      // do nothing
    }
  };

  struct data {

    std::vector<SnailNumber> nums;
    data() noexcept = default;
    data(data const&) noexcept = delete;
    data(data&&) noexcept = default;
    data& operator=(data const&) noexcept = delete;
    data& operator=(data&&) noexcept = default;

    inline ~data() {
      Deleter d;
      for (auto& n : nums) {
        std::visit(d, n);
      }
    }
  };

  constexpr const int id = 18;
  using parsed = data;

  template <bool part2>
  using answer = int;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
