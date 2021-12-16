#include <catch2/catch_all.hpp>

#include "AdventTest.hpp"
#include "AdventDay.hpp"
#include "Day16.hpp"

using namespace day16;

namespace {

auto const input_part1 = std::array {
    "8A004A801A8002F478",
    "620080001611562C8802118E34",
    "C0015000016115A2E0802F182340",
    "A0016C880162017C3686B18A3D4780"
};

auto const input_part2 = std::array {
    "C200B40A82",
    "04005AC33890",
    "880086C3E88112",
    "CE00C43D881120",
    "D8005AC2A8F0",
    "F600BC2D8F",
    "9C005AC2F8F0",
    "9C0141080250320F1802104A08"
};

auto const expected_part1 = std::array { 16l, 12l, 23l, 31l };
auto const expected_part2 = std::array {  3l,  54l,  7l,  9l, 1l, 0l, 0l, 1l };
using Day = AdventDay<id, parsed, result1, result2>;

}

SCENARIO("2021.day.16","[2021][16]") {
    GIVEN("Part 1 Sample Data") {
        for (unsigned i{0}; i < std::size(input_part1); ++i) {
            tmp_file sample{id};
            sample.append(input_part1[i]);
            auto parsed = Day::parse(sample.name());
            WHEN("Running Part 1 on input ") {
                THEN("We get the correct answer") {
                    INFO("input is " << input_part1[i]);
                    auto actual = Day::solve<false>(parsed);
                    REQUIRE(actual == expected_part1[i]);
                }
            }
        }
    }
    GIVEN("Part 2 Sample Data") {
        for (unsigned i{0}; i < std::size(input_part2); ++i) {
            tmp_file sample{id};
            sample.append(input_part2[i]);
            auto parsed = Day::parse(sample.name());
            WHEN("Running Part 2 on input ") {
                INFO("input is " << input_part2[i]);
                auto actual = Day::solve<true>(parsed);
                THEN("We get the correct answer") {
                    REQUIRE(actual == expected_part2[i]);
                }
            }
        }
    }
}
