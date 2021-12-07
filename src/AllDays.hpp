#pragma once

#include <tuple>

#include "AdventDay.hpp"

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
