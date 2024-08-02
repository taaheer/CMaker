#include "Utility.h"

#include <string>   // for strings    
#include <cctype>   // for std::isfigit()
#include <algorithm> // for std::all_of, std::transform
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

bool Utility::isNumericStringInRange(const std::string &str, const std::size_t arraySize)
{
    if(str.empty())
    {
        std::cerr << "Error: input was empy\n";
        return false;
    }
    else if(isStringNumeric(str))
    {
        int num{std::stoi(str)};

        if(num >= 0 && num < static_cast<int>(arraySize))
        {
            return true;
        }

        std::cerr << "Error: not within range\n";
        return false;
    }
    
    std::cerr << "Error: not a number\n";

    return false;
}

std::string Utility::toLowerCase(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){return std::tolower(c);});

    return str;
}
