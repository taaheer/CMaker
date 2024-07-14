#ifndef UTILITY_H
#define UTILITY_H

#include <string>   // for strings    

namespace Utility
{
    // check if string is numeric decimal.
    bool isStringNumeric(const std::string &str);
    bool isStringHasSpace(const std::string &str);
    bool isFileExist(const std::string &str);
}

#endif
