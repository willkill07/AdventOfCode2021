#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day02.hpp"

using namespace day02;

namespace {

char const* input = R"MULTILINE(forward 5
down 5
forward 8
up 3
down 8
forward 2
)MULTILINE";

auto const expected_part1 = 150;
auto const expected_part2 = 900;
using Day = AdventDay<id, parsed, result1, result2>;

}

SCENARIO("2021.day.02","[2021][02]") {
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
