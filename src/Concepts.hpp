#pragma once

#include <concepts>
#include <optional>
#include <string>
#include <utility>

template <typename D>
concept advent_day = requires {
  typename D::parsed_type;
  typename D::part1_answer;
  typename D::part2_answer;
  typename D::opt_answer;

  typename D::template answer<false>;
  typename D::template answer<true>;
  requires std::same_as<typename D::part1_answer, typename D::template answer<false>>;
  requires std::same_as<typename D::part2_answer, typename D::template answer<true>>;
  requires std::same_as<typename D::opt_answer, std::optional<typename D::part1_answer>>;

  { D::name() } -> std::same_as<std::string>;
  { D::input_file() } -> std::same_as<std::string>;

  requires requires (std::string const& str) {
    { D::parse(str) } -> std::same_as<typename D::parsed_type>;
  };
  
  requires requires (typename D::parsed_type const& parsed_args, typename D::opt_answer part1_answer) {
    { D::template solve<false>(parsed_args, part1_answer) } -> std::same_as<typename D::part1_answer>;
    { D::template solve<true>(parsed_args, part1_answer) } -> std::same_as<typename D::part2_answer>;
  };
};

