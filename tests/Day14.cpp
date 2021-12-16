#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day14.hpp"

using namespace day14;

namespace {

char const* input = R"MULTILINE(NNCB

CH -> B
HH -> N
CB -> H
NH -> C
HB -> C
HC -> B
HN -> C
NN -> C
BH -> H
NC -> B
NB -> B
BN -> B
BB -> N
BC -> B
CC -> N
CN -> C)MULTILINE";

auto const expected_part1 = 1588l;
auto const expected_part2 = 2188189693529l;
using Day = AdventDay<id, parsed, result1, result2>;

}

SCENARIO("2021.day.14","[2021][14]") {
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
