#pragma once

#include <future>
#include <chrono>
#include <optional>
#include <stdexcept>
#include <string>
#include <array>
#include <type_traits>
#include <utility>
#include <variant>

#include <fmt/core.h>
#include <fmt/color.h>
#include <scn/all.h>


#include "AdventDay.hpp"
#include "Concepts.hpp"
#include "Utils.hpp"

#include "Day01.hpp"
#include "Day02.hpp"
#include "Day03.hpp"
#include "Day04.hpp"
#include "Day05.hpp"
#include "Day06.hpp"

using ALL_ADVENT_DAYS = std::tuple<
  AdventDay<day01::id, day01::parsed, day01::result1, day01::result2>,
  AdventDay<day02::id, day02::parsed, day02::result1, day02::result2>,
  AdventDay<day03::id, day03::parsed, day03::result1, day03::result2>,
  AdventDay<day04::id, day04::parsed, day04::result1, day04::result2>,
  AdventDay<day05::id, day05::parsed, day05::result1, day05::result2>,
  AdventDay<day06::id, day06::parsed, day06::result1, day06::result2>
>;

template <int N>
using get_day = std::tuple_element_t<N - 1, ALL_ADVENT_DAYS>;

namespace detail {
      
  template <advent_day Day>
  result<Day>
  run_impl(types::options const & opts) {
    result<Day> res;
    typename Day::parsed_type parsed;
    {
      auto const start = time_clock::now();
      parsed = Day::parse(Day::input_file().c_str());
      auto const stop = time_clock::now();
      if (not std::holds_alternative<types::Run>(opts.modes))
        res.times.parse = std::chrono::duration<double, time_resolution>(stop - start).count();
    }
    if (std::holds_alternative<types::All>(opts.parts)
        or std::get<types::Part>(opts.parts).part == 1) {
      auto const start = time_clock::now();
      res.answers.part1 = Day::template solve<false>(parsed);
      auto const stop = time_clock::now();
      if (not std::holds_alternative<types::Run>(opts.modes))
        res.times.part1 = std::chrono::duration<double, time_resolution>(stop - start).count();
    }
    if (std::holds_alternative<types::All>(opts.parts)
        or std::get<types::Part>(opts.parts).part == 2) {
      auto const start = time_clock::now();
      res.answers.part2 = Day::template solve<true>(parsed, res.answers.part1);
      auto const stop = time_clock::now();
      if (not std::holds_alternative<types::Run>(opts.modes))
        res.times.part2 = std::chrono::duration<double, time_resolution>(stop - start).count();
    }
    return res;
  }

  template <advent_day Day>
  void
  run(types::options const & opts) {
      run_impl<Day>(opts).print(opts);
  }

  template <advent_day Day>
  void
  benchmark(types::options const & opts) {
    auto const ntimes = std::get<types::Benchmark>(opts.modes).ntimes;
    result<Day> res;
    std::visit(Overload{
      [&] (types::All) {
        res.times.part1 = 0.0;
        res.times.part2 = 0.0;
      },
      [&] (types::Part p) {
        if (p.part == 1) {
          res.times.part1 = 0.0;
        } else {
          res.times.part2 = 0.0;
        }
      }
    }, opts.parts);
    for (int i = 0; i < ntimes; ++i) {
        auto const tmp = run_impl<Day>(opts);
        res.times.parse += tmp.times.parse;
        if (res.times.part1) *res.times.part1 += *tmp.times.part1;
        if (res.times.part2) *res.times.part2 += *tmp.times.part2;
    }
    res.times.parse /= ntimes;
    if (res.times.part1) *res.times.part1 /= ntimes;
    if (res.times.part2) *res.times.part2 /= ntimes;
    res.print(opts);
  }

  using callable = void(*)(types::options const &);

  constexpr auto const all_benchmarks =
    [] <std::size_t... Days> (std::index_sequence<Days...>) constexpr {
      std::array<callable, sizeof...(Days)> result;
      (
        (result[Days] = [] (types::options const& opts) {
          benchmark<std::tuple_element_t<Days, ALL_ADVENT_DAYS>>(opts);
        }), ...
      );
      return result;
    } (std::make_index_sequence<std::tuple_size_v<ALL_ADVENT_DAYS>>{});

  constexpr auto const all_runs =
    [] <std::size_t... Days> (std::index_sequence<Days...>) constexpr {
      std::array<callable, sizeof...(Days)> result;
      (
        (result[Days] = [] (types::options const& opts) {
          run<std::tuple_element_t<Days, ALL_ADVENT_DAYS>>(opts);
        }), ...
      );
      return result;
    } (std::make_index_sequence<std::tuple_size_v<ALL_ADVENT_DAYS>>{});

  void run_single(types::options const & opts, std::size_t day) {
    std::visit(Overload{
      [&] (types::Benchmark) {
        all_benchmarks[day - 1](opts);
      },
      [&] (auto) {
        if (day > std::tuple_size_v<ALL_ADVENT_DAYS>) {
          throw std::runtime_error{"Invalid day specified"};
        }
        all_runs[day - 1](opts);
      }
    }, opts.modes);
  }
}

void
invoke(types::options const & opts) {
  std::visit(Overload{
    [&] (types::Day const & day) {
      detail::run_single(opts, std::size_t(day.day));
    },
    [&] (auto&&) {
      for (std::size_t day = 1; day <= std::tuple_size_v<ALL_ADVENT_DAYS>; ++day) {
        detail::run_single(opts, day);
      }
    }
  }, opts.days);
}
