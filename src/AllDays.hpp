#pragma once

#include <tuple>

#include "AdventDay.hpp"

#include "Day01.hpp"
#include "Day02.hpp"
#include "Day03.hpp"
#include "Day04.hpp"
#include "Day05.hpp"
#include "Day06.hpp"
#include "Day07.hpp"
#include "Day08.hpp"
#include "Day09.hpp"
#include "Day10.hpp"
#include "Day11.hpp"
#include "Day12.hpp"
#include "Day13.hpp"
#include "Day14.hpp"
#include "Day15.hpp"
#include "Day16.hpp"
#include "Day17.hpp"
#include "Day18.hpp"
#include "Day19.hpp"
#include "Day20.hpp"
#include "Day21.hpp"

using ALL_ADVENT_DAYS = std::tuple<
  AdventDay<day01::id, day01::parsed, day01::result1, day01::result2>,
  AdventDay<day02::id, day02::parsed, day02::result1, day02::result2>,
  AdventDay<day03::id, day03::parsed, day03::result1, day03::result2>,
  AdventDay<day04::id, day04::parsed, day04::result1, day04::result2>,
  AdventDay<day05::id, day05::parsed, day05::result1, day05::result2>,
  AdventDay<day06::id, day06::parsed, day06::result1, day06::result2>,
  AdventDay<day07::id, day07::parsed, day07::result1, day07::result2>,
  AdventDay<day08::id, day08::parsed, day08::result1, day08::result2>,
  AdventDay<day09::id, day09::parsed, day09::result1, day09::result2>,
  AdventDay<day10::id, day10::parsed, day10::result1, day10::result2>,
  AdventDay<day11::id, day11::parsed, day11::result1, day11::result2>,
  AdventDay<day12::id, day12::parsed, day12::result1, day12::result2>,
  AdventDay<day13::id, day13::parsed, day13::result1, day13::result2>,
  AdventDay<day14::id, day14::parsed, day14::result1, day14::result2>,
  AdventDay<day15::id, day15::parsed, day15::result1, day15::result2>,
  AdventDay<day16::id, day16::parsed, day16::result1, day16::result2>,
  AdventDay<day17::id, day17::parsed, day17::result1, day17::result2>,
  AdventDay<day18::id, day18::parsed, day18::result1, day18::result2>,
  AdventDay<day19::id, day19::parsed, day19::result1, day19::result2>,
  AdventDay<day20::id, day20::parsed, day20::result1, day20::result2>,
  AdventDay<day21::id, day21::parsed, day21::result1, day21::result2>
>;
