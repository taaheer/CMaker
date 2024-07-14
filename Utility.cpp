#include "Utility.h"

#include <string>   // for strings    
#include <cctype>   // for std::isfigit()
#include <algorithm> // for std::all_of
#include <filesystem> // for std::filesystem::exists()

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

bool Utility::isFileExist(const std::string &str)
{
    return std::filesystem::exists(str);
}
