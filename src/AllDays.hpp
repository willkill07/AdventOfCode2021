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
  AdventDay<day10::id, day10::parsed, day10::result1, day10::result2>
>;
