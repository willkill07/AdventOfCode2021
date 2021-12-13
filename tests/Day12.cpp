#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day12.hpp"

using namespace day12;

namespace {

std::array<char const*,3> input = {

R"MULTILINE(start-A
start-b
A-c
A-b
b-d
A-end
b-end)MULTILINE",

R"MULTILINE(dc-end
HN-start
start-kj
dc-start
dc-HN
LN-dc
HN-end
kj-sa
kj-HN
kj-dc)MULTILINE",

R"MULTILINE(fs-end
he-DX
fs-he
start-DX
pj-DX
end-zg
zg-sl
zg-pj
pj-he
RW-he
fs-DX
pj-RW
zg-RW
start-pj
he-WI
zg-he
pj-fs
start-RW)MULTILINE"

};

std::array const expected_part1 = { 10u, 19u, 226u };
std::array const expected_part2 = { 36u, 109u, 3509u };
using Day = AdventDay<id, parsed, result1, result2>;

}

SCENARIO("2021.day.12","[2021][12]") {
    GIVEN("Smallest sample input") {

        tmp_file sample{id};
        sample.append(input[0]);
        auto parsed = Day::parse(sample.name());

        WHEN("Running Part 1") {
            auto actual = Day::solve<false>(parsed);
            THEN("We get the correct answer") {
                REQUIRE(actual == expected_part1[0]);
            }
        }

        WHEN("Running Part 2") {
            auto actual = Day::solve<true>(parsed);
            THEN("We get the correct answer") {
                REQUIRE(actual == expected_part2[0]);
            }
        }
    }
    
    GIVEN("Medium sample input") {

        tmp_file sample{id};
        sample.append(input[1]);
        auto parsed = Day::parse(sample.name());

        WHEN("Running Part 1") {
            auto actual = Day::solve<false>(parsed);
            THEN("We get the correct answer") {
                REQUIRE(actual == expected_part1[1]);
            }
        }

        WHEN("Running Part 2") {
            auto actual = Day::solve<true>(parsed);
            THEN("We get the correct answer") {
                REQUIRE(actual == expected_part2[1]);
            }
        }
    }
    
    GIVEN("Largest sample input") {

        tmp_file sample{id};
        sample.append(input[2]);
        auto parsed = Day::parse(sample.name());

        WHEN("Running Part 1") {
            auto actual = Day::solve<false>(parsed);
            THEN("We get the correct answer") {
                REQUIRE(actual == expected_part1[2]);
            }
        }

        WHEN("Running Part 2") {
            auto actual = Day::solve<true>(parsed);
            THEN("We get the correct answer") {
                REQUIRE(actual == expected_part2[2]);
            }
        }
    }
}
