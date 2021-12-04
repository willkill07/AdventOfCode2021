#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day01.hpp"

namespace {

char const* input = R"MULTILINE(199
200
208
210
200
207
240
269
260
263)MULTILINE";

auto const expected_part1 = 7;
auto const expected_part2 = 5;
using Day = AdventDay<day01::id, day01::parsed, day01::result1, day01::result2>;
constexpr int day = day01::id;

}

SCENARIO("2021.day.01","[day01]") {
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
