#include "CMake.h"

#include <iostream>     // for input and output
#include <fstream>      // for creating file
#include <filesystem>   // for deleting file
#include <iostream>     // for input and output
#include <cctype>       // for std::isfigit()
#include <string>       // for strings and std::stod

std::string CMake::addHeader() const
{
    return "# This was generated by CMaker\n"
    "# With modern pratice and suggestion from https://cliutils.gitlab.io/modern-cmake/\n\n";
}

std::string CMake::getCMakeVersion() const
{
    std::string input{};
    do
    {
        std::cout << "Enter version: ";

        std::getline(std::cin, input);
    }
    while(!isCMakeVersionValid(input));

    if(input.empty())
    {
        return defaultVersion;
    }
    else
    {
        return input;
    }
}

bool CMake::isCMakeVersionValid(const std::string &input) const
{
    if(input.empty())
    {
        return true;
    }
    else if(isNumeric(input))
    {
        double inputVersion(std::stod(input));

        if(inputVersion < 0)
        {
            std::cerr << "Error: there is no negative version and never will be\n";
            return false;
        }
        else if(inputVersion < leastMinimumVersion)
        {
            std::cerr << "Warning: your chosen version is less than " << leastMinimumVersion 
            << " which is minimum for many modern practices, released in June 2014\n";
        }
        else if(inputVersion> latestAvailableVersion)
        {
            std::cerr << "Warning: either " << inputVersion << " does not exist yet, or my app is not updated.\n" 
            "Please check out https://cmake.org/download/ and raise and pull request if software is lagging behind\n";
        }

        return true;
    }
    else
    {
        std::cerr << "Error: wrong input, please enter correct minimum version\n";
        return false;
    }
}

bool CMake::isNumeric(const std::string &input) const
{
    return std::all_of(input.begin(), input.end(), [](char c)
    {
        return std::isdigit(c) || c == '.';
    });
}

void CMake::generateCMake([[maybe_unused]]std::size_t count) const
{
    std::cout << "Generating " << gFilename << '\n';

    std::ofstream cmake{gFilename};
    if(!cmake.is_open())
    {
        std::cerr << "Failed to generate " << gFilename << '\n';
        return;
    }

    cmake << addHeader();
    cmake << "cmake_minimum_required(VERSION " << getCMakeVersion() << ")\n\n";
    // cmake << "project(" << getProjectName() << " VERSION " << getProjectVersion() << " DESCRIPTION " << getProjectDescription() << " LANGUAGES " << getProjectLanguage() <<")\n\n";


    cmake.close();

    std::cout << gFilename << " generated successfully\n";
}

void CMake::removeCMake([[maybe_unused]]std::size_t count) const
{
    std::cout << "Removing " << gFilename << '\n';

    if(std::filesystem::exists(gFilename))
    {
        std::cout << gFilename << " found\n";

        if(std::filesystem::remove(gFilename))
        {
            std::cout << "Removed\n";
        }
        else
        {
            std::cerr << "Error removing\n";
        }
    }
    else
    {
        std::cerr << gFilename << " not found\n";
    }
}