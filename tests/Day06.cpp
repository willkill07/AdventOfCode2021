#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day06.hpp"

using namespace day06;

namespace {

char const* input = R"MULTILINE(3,4,3,1,2
)MULTILINE";

auto const expected_part1 = 5934llu;
auto const expected_part2 = 26984457539llu;
using Day = AdventDay<id, parsed, result1, result2>;

}

SCENARIO("2021.day.06","[2021][06]") {
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
