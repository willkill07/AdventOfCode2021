#pragma once

#include <algorithm>
#include <type_traits>
#include <variant>
#include <vector>

namespace day16 {

  struct Literal {
    std::uint8_t version;
    std::int64_t value;
  };

  struct Operator {
    std::uint8_t version;
    std::uint8_t type;
    std::vector<std::variant<Literal, Operator>> operands;
  };

  using Node = std::variant<Literal, Operator>;

  struct VersionAdder {

    inline long operator()(Literal const& l) const {
      return static_cast<long>(l.version);
    }

    inline long operator()(Operator const& o) const {
      auto sum = static_cast<long>(o.version);
      for (auto& s : o.operands) {
        sum += std::visit(*this, s);
      }
      return sum;
    }
  };

  struct Evaluator {

    inline long operator()(Literal const& l) const {
      return static_cast<long>(l.value);
    }

    inline long operator()(Operator const& o) const {
      long result;
      switch (o.type) {
        case 0: // sum
        {
          result = 0;
          for (auto& ops : o.operands) {
            result += std::visit(*this, ops);
          }
          break;
        }
        case 1: // product
        {
          result = 1;
          for (auto& ops : o.operands) {
            result *= std::visit(*this, ops);
          }
          break;
        }
        case 2: // min
        {
          result = std::numeric_limits<long>::max();
          for (auto& ops : o.operands) {
            result = std::min(result, std::visit(*this, ops));
          }
          break;
        }
        case 3: // max
        {
          result = std::numeric_limits<long>::min();
          for (auto& ops : o.operands) {
            result = std::max(result, std::visit(*this, ops));
          }
          break;
        }
        case 5: // greater
        {
          auto arg1 = std::visit(*this, o.operands[0]);
          auto arg2 = std::visit(*this, o.operands[1]);
          result = static_cast<long>(arg1 > arg2);
          break;
        }
        case 6: // less
        {
          auto arg1 = std::visit(*this, o.operands[0]);
          auto arg2 = std::visit(*this, o.operands[1]);
          result = static_cast<long>(arg1 < arg2);
          break;
        }
        case 7: // equal
        {
          auto arg1 = std::visit(*this, o.operands[0]);
          auto arg2 = std::visit(*this, o.operands[1]);
          result = static_cast<long>(arg1 == arg2);
          break;
        }
        default:
        {
          result = 0;
        }
      }
      return result;
    }
  };

  constexpr const int id = 16;
  using parsed = Node;

  template <bool part2>
  using answer = long;
  using result1 = answer<false>;
  using result2 = answer<true>;
}
