#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day11.hpp"

using namespace day11;

namespace {

char const* input = R"MULTILINE(5483143223
2745854711
5264556173
6141336146
6357385478
4167524645
2176841721
6882881134
4846848554
5283751526)MULTILINE";

auto const expected_part1 = 1656;
auto const expected_part2 = 195;
using Day = AdventDay<id, parsed, result1, result2>;

}

SCENARIO("2021.day.11","[2021][11]") {
    GIVEN("Sample input") {

        tmp_file sample{id};
        sample.append(input);
        auto parsed = Day::parse(sample.name());

        WHEN("Running Part 1") {
            auto actual = Day::solve<false>(parsed);
            THEN("We get the correct answer") {
                REQUIRE(actual == expected_part1);
            }
        }

        AND_WHEN("Running Part 2") {
            auto actual = Day::solve<true>(parsed);
            THEN("We get the correct answer") {
                REQUIRE(actual == expected_part2);
            }
        }
    }
}
