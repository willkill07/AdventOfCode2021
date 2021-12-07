#pragma once

#include <concepts>

#include <scn/all.h>

template <typename T>
concept scannable = requires (T& t, scn::basic_parse_context<scn::basic_default_locale_ref<char>>& ctx) {
  { t.scan(ctx) } -> std::same_as<scn::error>;
};

template <typename CharT, scannable MyType>
struct scn::scanner<CharT, MyType> : scn::empty_parser {
  template <typename Context>
  error
  scan(MyType& val, Context& ctx) {
    return val.scan(ctx);
  }
};
