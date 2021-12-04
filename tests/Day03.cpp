#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDays.hpp"

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

constexpr int day = 3;
auto const expected_part1 = 198;
auto const expected_part2 = 230;
using Day = get_day<day>;

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
