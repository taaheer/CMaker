#include "Utility.h"

#include <string>   // for strings    
#include <cctype>   // for std::isfigit()
#include <algorithm> // for std::all_of

bool Utility::isStringNumeric(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), [](char c)
    {
        return std::isdigit(c) || c == '.';
    });
}

bool Utility::isStringHasSpace(const std::string &str)
{
    return str.find_first_not_of("\t\n ") == str.npos;
}
