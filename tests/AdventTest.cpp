
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/os.h>

#include "AdventTest.hpp"

namespace fs = std::filesystem;

tmp_file::tmp_file(int day)
: file {fs::temp_directory_path() / fmt::format("day{:02d}_sample.txt", day)}
{

}

tmp_file::~tmp_file() {
    std::filesystem::remove(file);
}

void
tmp_file::append(std::string_view info) {
    auto out = fmt::output_file(file.c_str());
    out.print("{}", info);
    out.close();
}

char const*
tmp_file::name() const {
    return file.c_str();
}