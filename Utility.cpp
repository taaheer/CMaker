#include "Utility.h"

#include <string>   // for strings    
#include <cctype>   // for std::isfigit()
#include <algorithm> // for std::all_of

bool Utility::isNumeric(const std::string & str)
{
    return std::all_of(str.begin(), str.end(), [](char c)
    {
        return std::isdigit(c) || c == '.';
    });
}
