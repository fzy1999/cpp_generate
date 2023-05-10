#include <cstdio>
#include <tclap/UnlabeledMultiArg.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "parser/parser_cpp.h"
#include "tools/files.h"
#include "tools/to_filename.h"
#include "clang/AST/ASTTypeTraits.h"

// tclap
#include "tclap/CmdLine.h"

// inja
#include "inja/inja.hpp"
#include "inja/template.hpp"
#define DEBUG 0

using json = nlohmann::json;
void config_from_json(const json &j, Config &p) {
  j.at("compdb_dir").get_to(p.compdb_dir);
  j.at("header").get_to(p.templates.header);
  j.at("for_enum").get_to(p.templates.for_enum);
  j.at("object").get_to(p.templates.object);
  j.at("input").get_to(p.input);
  j.at("output_dir").get_to(p.output_dir);
  j.at("output_file").get_to(p.output_file);
}

Config parse_config(std::string c_path) {
  std::ifstream input;
  if (1) {
    c_path = "../config.json"; // debug
  }
  input.open(c_path);

  if (!input.is_open()) {
    std::cerr << "Cannot find the config file, aborted" << std::endl;
    exit(1);
  }
  Config conf;
  auto data = nlohmann::json::parse(input);
  if (DEBUG) {
    conf = Config{"../build",
                  Config::Templates{"../generator/test/templates/header.inja",
                                    "../generator/templates/registor.inja",
                                    "../generator/templates/registor.inja"},
                  {"../generator/test/data/exampleClass.h"},
                  "../generator/test/generated",
                  "registor.h"};
  } else {
    config_from_json(data, conf);
  }
  input.close();
  return conf;
}

void generate_header(std::ofstream &ofs, const std::string &header) {
  std::ifstream input;
  input.open(header);
  if (!input.is_open()) {
    std::cerr << "Cannot find the header file, aborted" << std::endl;
    exit(1);
  }
  std::string line;
  while (std::getline(input, line)) {
    ofs << line << std::endl;
  }
  input.close();
}

void generate_file(const Config &conf) {
  // parse source files
  ParserCpp parser(conf.compdb_dir, //
                   conf.input,      //
                   conf.output_dir);

  auto parsed = parser.parse();
  std::filesystem::path fs_output_dir(conf.output_dir);

  // check output directory
  if (std::filesystem::exists(fs_output_dir)) {
    std::filesystem::remove_all(fs_output_dir);
  }
  std::filesystem::create_directory(fs_output_dir);
  // load templates
  inja::Environment inja_env;
  auto template_header = inja_env.parse_template(conf.templates.header);
  auto template_object = inja_env.parse_template(conf.templates.object);
  auto template_enum = inja_env.parse_template(conf.templates.for_enum);
  auto registor_fname = fs_output_dir / conf.output_file;
  std::ofstream registor(registor_fname, std::ifstream::app);

  std::stringstream include_lines;
  std::stringstream entities;
  std::unordered_set<std::string>
      include_lines_set; // in case of duplicated include
  // generate templates
  for (auto &&[object_name, json] : parsed) {
    if (include_lines_set.find(json.at("origin").get<std::string>()) ==
        include_lines_set.end()) {
      include_lines << inja_env.render("#include \"{{ origin }}\" \n", json);
      include_lines_set.insert(json.at("origin").get<std::string>());
    }
    if (json["id"].get<int>() == 0) {
      inja_env.render_to(entities, template_object, json);
    } else {
      inja_env.render_to(entities, template_enum, json);
    }
  }
  json all;
  all["include_lines"] = include_lines.str();
  all["entities"] = entities.str();
  inja_env.render_to(registor, template_header, all);
  registor.close();
}

////////////////////////////////////
int main(int argc, const char **argv) {
  TCLAP::CmdLine cmd("Easy Reflection code generator");

  Files file_manager;
  auto fname = file_manager.root();
  TCLAP::ValueArg<std::string> c_arg(
      "c", "config",
      "Explicitly specify path to the config file", //
      false, file_manager.root() + "../config.json", "path");

  TCLAP::SwitchArg p_arg("p", "perf", "Print performance report", false);

  cmd.add(c_arg);
  cmd.add(p_arg);
  cmd.ignoreUnmatched(true);
  cmd.parse(argc, argv);

  std::string c_path = c_arg.getValue();
  std::cout << "begin generating " << c_path << std::endl;

  auto time_1 = std::chrono::steady_clock::now();
  auto conf = parse_config(c_path);
  // correct pathes and find all files recursive inside input folders
  file_manager.correct_config(&conf);

  auto time_2 = std::chrono::steady_clock::now();
  // begin rendering
  generate_file(conf);

  if (!p_arg.getValue()) {
    return 0;
  }
  auto time_3 = std::chrono::steady_clock::now();
  auto analysis = std::chrono::duration<double>(time_2 - time_1).count();
  auto generation =
      std::chrono::duration_cast<std::chrono::milliseconds>(time_3 - time_2)
          .count();
  auto all = std::chrono::duration<double>(time_3 - time_1).count();

  printf("analysis %f sec, generation %f ms, all %f sec\n", analysis,
         generation, all);

  return 0;
}