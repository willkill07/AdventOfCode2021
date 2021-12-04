#pragma once

#include <concepts>
#include <optional>
#include <string>
#include <utility>


template <typename D>
concept advent_day = requires {
  typename D::parsed_type;
  typename D::answer_one_type;
  typename D::answer_two_type;
  { D::name() } -> std::same_as<std::string>;
  { D::input_file() } -> std::same_as<std::string>;
  requires requires (char const * cstr) {
    { D::parse(cstr) } -> std::same_as<typename D::parsed_type>;
  };
  requires requires (typename D::parsed_type const& parsed_args, std::optional<typename D::answer_one_type> part1_answer) {
    { D::template solve<false>(parsed_args, part1_answer) } -> std::same_as<typename D::answer_one_type>;
    { D::template solve<true>(parsed_args, part1_answer) } -> std::same_as<typename D::answer_two_type>;
  };
};

