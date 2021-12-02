#pragma once

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/os.h>

#include <filesystem>
namespace fs = std::filesystem;

struct tmp_file {

    inline tmp_file(int day)
    : file {fs::temp_directory_path() / fmt::format("day{:02d}_sample.txt", day)}
    {

    }

    inline ~tmp_file() {
        std::filesystem::remove(file);
    }

    inline void
    append(std::string_view info) {
        auto out = fmt::output_file(file.c_str());
        out.print("{}", info);
        out.close();
    }

    inline char const*
    name() const {
        return file.c_str();
    }

private:
    std::filesystem::path file;
};
