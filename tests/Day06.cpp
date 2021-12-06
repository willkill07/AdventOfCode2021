#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day06.hpp"

namespace {

char const* input = R"MULTILINE(3,4,3,1,2
)MULTILINE";

auto const expected_part1 = 5934llu;
auto const expected_part2 = 26984457539llu;
using Day = AdventDay<day06::id, day06::parsed, day06::result1, day06::result2>;
constexpr int day = day06::id;

}

SCENARIO("2021.day.06","[day06]") {
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
