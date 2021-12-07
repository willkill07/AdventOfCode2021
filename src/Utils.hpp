#pragma once

#include <chrono>
#include <ratio>
#include <variant>

#include <fmt/color.h>
#include <fmt/core.h>
#include <locale>

#include "Concepts.hpp"

constexpr auto time_symbol = "us";
using time_resolution      = std::micro;
using time_clock           = std::chrono::steady_clock;

template <typename... Ts>
struct Overload : Ts... {
  using Ts::operator()...;
};

template <class... Ts>
Overload(Ts...) -> Overload<Ts...>;

namespace types {

struct Run {};
struct Time {};
struct All {};
struct Benchmark {
  unsigned ntimes;
};
struct Day {
  unsigned day;
};
struct Part {
  unsigned part;
};

using mode = std::variant<Run, Time, Benchmark>;
using day  = std::variant<All, Day>;
using part = std::variant<All, Part>;

struct options {
  mode modes;
  day  days;
  part parts;
};

} // namespace types

struct timings {
  double                parse;
  std::optional<double> part1;
  std::optional<double> part2;

  constexpr timings&
  operator+= (timings const& other) {
    parse += other.parse;
    if (part1) {
      *part1 += *other.part1;
    } else {
      part1 = other.part1;
    }
    if (part2) {
      *part2 += *other.part2;
    } else {
      part2 = other.part2;
    }
    return *this;
  }

  constexpr timings
  operator+ (timings const& other) const {
    return timings{*this} += other;
  }

  inline void
  print() const {
    fmt::print(fmt::emphasis::bold, "  Times:\n");
    fmt::print("    {:10s} ", "Parsing:");
    fmt::print(fg(fmt::terminal_color::blue), "{:13.3Lf} {}\n", parse, time_symbol);
    double total = parse;
    if (part1) {
      fmt::print("    {:10s} ", "Part 1:");
      fmt::print(fg(fmt::terminal_color::blue), "{:13.3Lf} {}\n", part1.value(), time_symbol);
      total += part1.value();
    }
    if (part2) {
      fmt::print("    {:10s} ", "Part 2:");
      fmt::print(fg(fmt::terminal_color::blue), "{:13.3Lf} {}\n", part2.value(), time_symbol);
      total += part2.value();
    }
    fmt::print("    {:10s} ", "Total:");
    fmt::print(fg(fmt::terminal_color::blue), "{:13.3Lf} {}\n", total, time_symbol);
  }
};

template <advent_day Day>
struct answers {
  std::optional<typename Day::part1_answer> part1;
  std::optional<typename Day::part2_answer> part2;
  
  inline void
  print() const {
    fmt::print(fmt::emphasis::bold, "  Answers:\n");
    if (part1) {
      fmt::print("    {:10s} ", "Part 1:");
      fmt::print(fg(fmt::terminal_color::green), "{:16}\n", part1.value());
    }
    if (part2) {
      fmt::print("    {:10s} ", "Part 2:");
      fmt::print(fg(fmt::terminal_color::green), "{:16}\n", part2.value());
    }
  }
};

template <advent_day Day>
struct result {
  timings      times;
  answers<Day> ans;

  inline void
  print(types::options const& opts) const {
    fmt::print(fg(fmt::terminal_color::bright_red) | fmt::emphasis::bold, "{}\n", Day::name());
    std::visit(
      Overload{
        [&](types::Benchmark) { },
        [&](auto) { ans.print(); }
      },
      opts.modes);

    std::visit(
      Overload{
        [&](types::Run) {},
        [&](auto) { times.print(); }
      },
      opts.modes);
  }
};
