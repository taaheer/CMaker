// For CLI stuffs
#include <CLI/CLI.hpp>


// custom class
#include "CMake.h"

#include <functional>   // for std::bind and std::placeholders::_1

int main(int argc, char **argv) 
{
    // if not argument was entetered
    if(argc == 1)
    {
        std::cerr << "Error: no operation specified (use -h or --help for help)\n";
        return -1;
    }

    // app description
    CLI::App app{"CMaker is a command line " + gFilename + "  generator"};

    CMake cmake{};

    app.set_version_flag("-v, --version", "0.1");

    app.add_flag("-R, --remove", std::bind(&CMake::removeCMake, &cmake, std::placeholders::_1), "Remove existing " + gFilename);

    app.add_flag("-M, --make", std::bind(&CMake::generateCMake, &cmake, std::placeholders::_1), "Generate " + gFilename);

    CLI11_PARSE(app, argc, argv);

    return 0;
}
