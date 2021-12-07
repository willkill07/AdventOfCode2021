#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

#include <fmt/core.h>
#include <fmt/color.h>
#include <scn/all.h>

#include "Concepts.hpp"
#include "Utils.hpp"

#include "AllDays.hpp"

namespace detail {

  template <auto V>
  using Const = std::integral_constant<decltype(V), V>;

  double
  time(std::invocable auto&& fn) {
    auto const start = time_clock::now();
    fn();
    auto const stop = time_clock::now();
    return std::chrono::duration<double, time_resolution>(stop - start).count();
  }
      
  template <advent_day Day>
  result<Day>
  run_impl(types::options const& opts) {
    result<Day> res;
    typename Day::parsed_type parsed;
    {
      auto const t = time([&] {
        parsed = Day::parse(Day::input_file().c_str());
      });
      if (not std::holds_alternative<types::Run>(opts.modes))
        res.times.parse = t;
    }
    /* always run part 1 */
    {
      auto const t = time([&] {
        res.ans.part1 = Day::template solve<false>(parsed);
      });
      if (std::holds_alternative<types::All>(opts.parts) or std::get<types::Part>(opts.parts).part == 1)
        if (not std::holds_alternative<types::Run>(opts.modes))
          res.times.part1 = t;
    }
    if (std::holds_alternative<types::All>(opts.parts) or std::get<types::Part>(opts.parts).part == 2) {
      auto const t = time([&] {
        res.ans.part2 = Day::template solve<true>(parsed, res.ans.part1);
      });
      if (not std::holds_alternative<types::Run>(opts.modes))
        res.times.part2 = t;
    }
    return res;
  }

  template <advent_day Day>
  void
  run(types::options const& opts) {
    run_impl<Day>(opts).print(opts);
  }

  template <advent_day Day>
  timings
  benchmark(types::options const& opts) {
    auto const ntimes = std::get<types::Benchmark>(opts.modes).ntimes;
    result<Day> res;
    auto const part_mask = std::visit(Overload{
      [&] (types::All) { return 3u; },
      [&] (types::Part p) { return p.part; }
    }, opts.parts);
    {
      res.times.parse = time([&] {
        for (auto i = 0u; i < ntimes; ++i) {
          Day::parse(Day::input_file().c_str());
        }
      }) / ntimes;
    }
    auto data = Day::parse(Day::input_file().c_str());
    if (part_mask & 1) {
      res.times.part1 = time([&] {
        for (auto i = 0u; i < ntimes; ++i) {
          Day::template solve<false>(data);
        }
      }) / ntimes;
    }
    auto part1_answer = Day::template solve<false>(data);
    if (part_mask & 2) {
      res.times.part2 = time([&] {
        for (auto i = 0u; i < ntimes; ++i) {
          Day::template solve<true>(data, part1_answer);
        }
      }) / ntimes;
    }
    res.print(opts);
    return res.times;
  }

  constexpr void
  for_each_day(auto&& fn) {
    [&] <std::size_t... Days> (std::index_sequence<Days...>) constexpr 
    {
      (fn(Const<Days>{}), ...);
    } (std::make_index_sequence<std::tuple_size_v<ALL_ADVENT_DAYS>>{});
  }

  constexpr auto const all_benchmarks = [] () constexpr {
    std::array<timings(*)(types::options const&), std::tuple_size_v<ALL_ADVENT_DAYS>> array;
    for_each_day([&] <std::size_t Day> (Const<Day>) constexpr {
      array[Day] = &benchmark<std::tuple_element_t<Day, ALL_ADVENT_DAYS>>;
    });
    return array;
  }();

  constexpr auto const all_runs = [] () constexpr {
    std::array<void(*)(types::options const&), std::tuple_size_v<ALL_ADVENT_DAYS>> array;
    for_each_day([&] <std::size_t Day> (Const<Day>) constexpr {
      array[Day] = &run<std::tuple_element_t<Day, ALL_ADVENT_DAYS>>;
    });
    return array;
  }();
}

void
invoke(types::options const& opts) {
  std::visit(Overload{
    [&] (types::Day const& day) {
      if (std::size_t(day.day) > std::tuple_size_v<ALL_ADVENT_DAYS>) {
        fmt::print(fg(fmt::terminal_color::bright_red), "{}", "ERROR: invalid day specified!\n");
      } else {
        std::visit(
          Overload{
            [&](types::Benchmark) { detail::all_benchmarks[day.day - 1](opts); },
            [&](auto) { detail::all_runs[day.day - 1](opts); }
          },
          opts.modes);
      }
    },
    [&] (auto&&) {
        std::visit(
          Overload{
            [&](types::Benchmark) {
              timings total{};
              detail::for_each_day([&] <std::size_t Day> (detail::Const<Day>) constexpr {
                total += detail::all_benchmarks[Day](opts);
              });
              fmt::print(fg(fmt::terminal_color::bright_green) | fmt::emphasis::bold, "{}\n", "Summary:");
              total.print();
            },
            [&](auto) {
              detail::for_each_day([&] <std::size_t Day> (detail::Const<Day>) constexpr {
                detail::all_runs[Day](opts);
              });
            }
          },
          opts.modes);
    }
  }, opts.days);
}
