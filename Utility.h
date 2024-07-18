#ifndef UTILITY_H
#define UTILITY_H

#include <string>   // for strings    
#include <iostream> // for std::cerr


namespace Utility
{
    // check if string is numeric decimal.
    bool isStringNumeric(const std::string &str);
    bool isStringHasSpace(const std::string &str);
    bool isSourceExist(const std::string &str);
    


    template <typename T, std::size_t N>
    bool isNumericStringInRange(const std::string &str, const std::array<T, N> &array)
    {
        if(str.empty())
        {
            std::cerr << "Error: input was empy\n";
            return false;
        }
        else if(isStringNumeric(str))
        {
            int num{std::stoi(str)};

            if(num >= 0 && num < static_cast<int>(array.size()))
            {
                return true;
            }

            std::cerr << "Error: not within range\n";
            return false;
        }
        
        std::cerr << "Error: not a number\n";

        return false;
    }

    template <typename T, std::size_t N>
    T getCorrespondingElementFromString(const std::string &str, const std::array<T, N> &array)
    {
        int num{std::stoi(str)};

        return array[static_cast<std::size_t>(num)];
    }

}

#endif
