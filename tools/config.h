#pragma once

#include <string>
#include <vector>

// keeps parsed UTF-8 strings even on Windows
struct Config {
  std::string compdb_dir;
  struct Templates {
    std::string header;
    std::string for_enum;
    std::string object;
  } templates;

  std::vector<std::string> input;
  std::string output_dir;
  std::string output_file; // for one-file generation
};
