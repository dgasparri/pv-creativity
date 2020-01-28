#define _USE_MATH_DEFINES
#include <algorithm>

#include "../config.h"
#include "../lib/panel_io.h"
#include "../lib/sun_fp.h"
#include "../lib/sun_panel_fp.h"
#include "../lib/geometry_fp.h"


#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

namespace po = boost::program_options


int main(int argc, char **argv) {
    std::string input;

    while (std::cin) {
        std::getline(std::cin, input);

        std::vector<std::string> parsedInput;
        boost::split(parsedInput, input, boost::is_any_of(" "), boost::token_compress_on);

        std::vector<char const*> args { "command" };
        for (auto& arg : parsedInput)
            args.push_back(arg.c_str());

        po::options_description desc("allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("compression", po::value<int>(), "set compression level")
        ;
        po::variables_map vm;
        po::store(po::parse_command_line(args.size(), args.data(), desc), vm);
        po::notify(vm);

        if (vm.count("help"))
            std::cout << desc << "\n";
    }
}

