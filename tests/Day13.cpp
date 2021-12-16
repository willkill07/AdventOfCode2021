#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day13.hpp"

using namespace day13;

namespace {

char const* input = R"MULTILINE(6,10
0,14
9,10
0,3
10,4
4,11
6,0
6,12
4,1
0,13
10,12
3,4
3,0
8,4
1,10
2,14
8,10
9,0

fold along y=7
fold along x=5)MULTILINE";

auto const expected_part1 = 17l;
auto const expected_part2 = std::string{'O'};
using Day = AdventDay<id, parsed, result1, result2>;

}

SCENARIO("2021.day.13","[2021][13]") {
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
