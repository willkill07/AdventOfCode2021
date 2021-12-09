#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day09.hpp"

using namespace day09;

namespace {

char const* input = R"MULTILINE(2199943210
3987894921
9856789892
8767896789
9899965678)MULTILINE";

auto const expected_part1 = 15;
auto const expected_part2 = 1134;
using Day = AdventDay<id, parsed, result1, result2>;

}

SCENARIO("2021.day.09","[2021][09]") {
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
