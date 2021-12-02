#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDays.hpp"

namespace {

char const* input = R"MULTILINE(forward 5
down 5
forward 8
up 3
down 8
forward 2
)MULTILINE";

constexpr int day = 2;
auto const expected_part1 = 150;
auto const expected_part2 = 900;
using Day = get_day<day>;

}

SCENARIO("2021.day.02","[day02]") {
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
