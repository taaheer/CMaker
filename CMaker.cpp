#include "CLI/App.hpp"
#include "CLI/Formatter.hpp"
#include "CLI/Config.hpp"

#include <iostream>

void generateCMake([[maybe_unused]]std::size_t count)
{
    std::cout << "Generating CMake\n";
}

void removeCMake([[maybe_unused]]std::size_t count)
{
    std::cout << "Removing CMake\n";
}

int main(int argc, char **argv) 
{
    CLI::App app{"CMaker is CLI CMake generator"};

    app.set_version_flag("-v, --version", "0.1");

    app.add_flag("-M, --make", generateCMake, "Generate CMake.txt");

    app.add_flag("-R, --remove", removeCMake, "Remove existing CMake.txt");

    CLI11_PARSE(app, argc, argv);

    return 0;
}
