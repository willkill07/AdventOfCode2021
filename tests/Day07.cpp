#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day07.hpp"

using namespace day07;

namespace {

char const* input = R"MULTILINE(16,1,2,0,4,2,7,1,2,14
)MULTILINE";

auto const expected_part1 = 37;
auto const expected_part2 = 168;
using Day = AdventDay<id, parsed, result1, result2>;

}

SCENARIO("2021.day.07","[2021][07]") {
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
