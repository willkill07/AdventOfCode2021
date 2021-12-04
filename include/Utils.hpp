#pragma once

#include <chrono>
#include <ratio>
#include <variant>

#include <fmt/color.h>
#include <fmt/core.h>
#include <locale>

#include "Concepts.hpp"

constexpr auto time_symbol = "µs";
using time_resolution      = std::micro;
using time_clock           = std::chrono::high_resolution_clock;

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
  int ntimes;
};
struct Day {
  int day;
};
struct Part {
  int part;
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

template <advent_day Day>
struct result {

  struct {
    double                parse;
    std::optional<double> part1;
    std::optional<double> part2;
  } times;

  struct {
    std::optional<typename Day::answer_one_type> part1;
    std::optional<typename Day::answer_two_type> part2;
  } answers;

  inline void
  print(types::options const& opts) const {
    fmt::print(fg(fmt::terminal_color::bright_red) | fmt::emphasis::bold, "{}\n", Day::name());
    std::visit(Overload{
      [&](types::Benchmark) { },
      [&](auto) {
        fmt::print(fmt::emphasis::bold, "  Answers:\n");
        if (answers.part1) {
          fmt::print("    {:10s} ", "Part 1:");
          fmt::print(fg(fmt::terminal_color::green), "{:16}\n", answers.part1.value());
        }
        if (answers.part2) {
          fmt::print("    {:10s} ", "Part 2:");
          fmt::print(fg(fmt::terminal_color::green), "{:16}\n", answers.part2.value());
        }
      }},
      opts.modes);

    std::visit(Overload{
      [&](types::Run) {},
      [&](auto) {
        fmt::print(fmt::emphasis::bold, "  Times:\n");
        fmt::print("    {:10s} ", "Parsing:");
        fmt::print(fg(fmt::terminal_color::blue), "{:13.3Lf} {}\n", times.parse, time_symbol);
        double total = times.parse;
        if (times.part1) {
          fmt::print("    {:10s} ", "Part 1:");
          fmt::print(fg(fmt::terminal_color::blue), "{:13.3Lf} {}\n", times.part1.value(), time_symbol);
          total += times.part1.value();
        }
        if (times.part2) {
          fmt::print("    {:10s} ", "Part 2:");
          fmt::print(fg(fmt::terminal_color::blue), "{:13.3Lf} {}\n", times.part2.value(), time_symbol);
          total += times.part2.value();
        }
        fmt::print("    {:10s} ", "Total:");
        fmt::print(fg(fmt::terminal_color::blue), "{:13.3Lf} {}\n", total, time_symbol);
      }},
      opts.modes);
  }
};
