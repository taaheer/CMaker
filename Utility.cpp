#include "Utility.h"

#include <string>   // for strings    
#include <cctype>   // for std::isfigit()
#include <algorithm> // for std::all_of
#include <filesystem> // for std::filesystem::exists()
#include <array> // for std::array

bool Utility::isStringNumeric(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), [](char c)
    {
        return std::isdigit(c) || c == '.';
    });
}

bool Utility::isStringHasSpace(const std::string &str)
{
    return str.find(' ') != str.npos;
}

bool Utility::isSourceExist(const std::string &str)
{
    if(std::filesystem::exists(str))
    {
        return true;
    }
    else
    {
        std::cerr << "Error: not found\n";
        return false;
    }
}
