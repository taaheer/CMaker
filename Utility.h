#ifndef UTILITY_H
#define UTILITY_H

#include <string>   // for strings    
#include <iostream> // for std::cerr
#include <sstream> // for std::ostringstream
#include <iomanip> // for std::setw and std::setfill


namespace Utility
{
    // check if string is numeric decimal.
    bool isStringNumeric(const std::string &str);
    bool isStringHasSpace(const std::string &str);
    bool isSourceExist(const std::string &str);
    bool isNumericStringInRange(const std::string &str, const std::size_t lastIndex);
    std::string toLowerCase(std::string str);


    template <typename T, std::size_t N>
    T getCorrespondingElementFromString(const std::string &str, const std::array<T, N> &array)
    {
        int num{std::stoi(str)};

        return array[static_cast<std::size_t>(num)];
    }

    template <typename T>
    std::string getStringDigitLengthOf(int length, T number)
    {
        std::ostringstream oss;
        oss << std::setw(length) << std::setfill('0') << number;
        return oss.str();
    }
}

#endif
