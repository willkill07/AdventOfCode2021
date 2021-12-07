#pragma once

#include <filesystem>

struct tmp_file {
  
  tmp_file(int day);
  ~tmp_file();
  void append(std::string_view info);
  std::string name() const;

private:
  std::filesystem::path file;
};
