#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day03.hpp"

namespace {

char const* input = R"MULTILINE(00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010
)MULTILINE";

auto const expected_part1 = 198;
auto const expected_part2 = 230;
using Day = AdventDay<day03::id, day03::parsed, day03::result1, day03::result2>;
constexpr int day = day03::id;

}

SCENARIO("2021.day.03","[day03]") {
    GIVEN("Sample input") {

        tmp_file sample{day};
        sample.append(input);
        auto parsed = Day::parse(sample.name());

        WHEN("Running Part 1") {
            auto actual = Day::solve<false>(parsed);
            THEN("We get the correct answer") {
                REQUIRE(actual == expected_part1);
            }
        }

        WHEN("Running Part 2") {
            auto actual = Day::solve<true>(parsed);
            THEN("We get the correct answer") {
                REQUIRE(actual == expected_part2);
            }
        }
    }
}
