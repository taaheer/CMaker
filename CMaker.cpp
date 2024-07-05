#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"

#include <fstream>
#include <iostream>

constexpr std::string gFilename{"CMakeLists.txt"};

void generateCMake([[maybe_unused]]std::size_t count)
{
    std::cout << "Generating " << gFilename << '\n';

    std::ofstream cmake{gFilename};
    if (!cmake.is_open())
    {
        std::cerr << "Failed to generate " << gFilename << '\n';
        return;
    }
    
    cmake.close();

    std::cout << gFilename << " generated successfully\n";
}

void removeCMake([[maybe_unused]]std::size_t count)
{
    std::cout << "Removing " << gFilename << '\n';
}

int main(int argc, char **argv) 
{
    if(argc == 1)
    {
        std::cerr << "Error: no operation specified (use -h or --help for help)\n";
        return -1;
    }

    CLI::App app{"CMaker is CLI CMake generator"};

    app.set_version_flag("-v, --version", "0.1");

    app.add_flag("-M, --make", generateCMake, "Generate " + gFilename);

    app.add_flag("-R, --remove", removeCMake, "Remove existing " + gFilename);

    CLI11_PARSE(app, argc, argv);

    return 0;
}
