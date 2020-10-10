//
// Created by Jelle Spijker on 10/10/20.
//

#include <spdlog/spdlog.h>
#include <docopt/docopt.h>
#include <range/v3/all.hpp>

constexpr char USAGE[] =
  R"(FFF

     Usage:
      FFF (-h | --help)
      FFF (-v | --verbose)
      FFF --version

    Options:
      -h --help     Show this screen
      -v --verbose  print more text
      --version     Show version
)";

int main(int argc, const char** argv)
{
  std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
    { argv + 1, argv + argc },
    true,
    "FFF 0.1");

  const auto key_views = args | ranges::views::keys;
  const auto enable_log = ranges::contains(key_views, "log");
  if (enable_log) {
    spdlog::set_level(spdlog::level::info);
  }

  for (const auto& arg : args) {
    spdlog::info("Command line argument {}: {}", arg.first, arg.second.asBool());
  }
  return 0;
}
