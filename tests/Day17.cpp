#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day17.hpp"

using namespace day17;

namespace {

char const* input = "x=20..30, y=-10..-5";

auto const expected_part1 = 45;
auto const expected_part2 = 112;
using Day = AdventDay<id, parsed, result1, result2>;

}

SCENARIO("2021.day.17","[2021][17]") {
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
