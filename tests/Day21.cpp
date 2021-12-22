#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day21.hpp"

using namespace day21;

namespace {

char const* input = R"MULTILINE(Player 1 starting position: 4
Player 2 starting position: 8)MULTILINE";

auto const expected_part1 = 739785u;
auto const expected_part2 = 444356092776315lu;
using Day = AdventDay<id, parsed, result1, result2>;

}

SCENARIO("2021.day.21","[2021][21]") {
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
