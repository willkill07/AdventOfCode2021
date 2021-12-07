#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day01.hpp"

using namespace day01;

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
263
)MULTILINE";

auto const expected_part1 = 7;
auto const expected_part2 = 5;
using Day = AdventDay<id, parsed, result1, result2>;

}

SCENARIO("2021.day.01","[2021][01]") {
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

        WHEN("Running Part 2") {
            auto actual = Day::solve<true>(parsed);
            THEN("We get the correct answer") {
                REQUIRE(actual == expected_part2);
            }
        }
    }
}
