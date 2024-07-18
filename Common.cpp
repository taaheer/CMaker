#include "Common.h"

#include "Utility.h"

#include <iostream>
#include <string>
#include <array>

bool Common::isContainReservedWords(const std::string &str)
{
    std::array<std::string, 3> cmakeListCommands{"cmake --help-command-list", "cmake --help-variable-list", "cmake --help-property-list"};

    // CppCheck is advicing to use std::any_of but when using std::any_of and lambda, it became slower and take more than with current code
    for(const std::string &command : cmakeListCommands)
    {
        static const std::set<std::string> listOfReservedCommand{getReservedListOf(command)};
        
        if(listOfReservedCommand.find(str) != listOfReservedCommand.end())
        {
            std::cerr << "Error: " << str << " is a reserved word\n";
            return true;
        }
    }

    return false;

}

std::set<std::string> Common::getReservedListOf(const std::string &argument)
{
    std::set<std::string> reservedWords{};
    std::array<char, 128> buffer{};
    FILE* pipe = popen(argument.c_str(), "r");

    if(!pipe)
    {
        std::cerr << "Error: failed to run cmake command";
        return reservedWords;
    }

    while(fgets(buffer.data(), buffer.size(), pipe) != nullptr) 
    {
        std::string word(buffer.data());
        word.erase(word.find_last_not_of(" \n\r\t")+1);
        reservedWords.insert(word);
    }

    pclose(pipe);
    return reservedWords;
}

bool Common::isNameValid(const std::string &name, const bool isEmptyEnterValid)
{
    if(name.empty())
    {
        if(!isEmptyEnterValid)
        {
            std::cerr << "Error: no input was provided\n";
        }

        return isEmptyEnterValid;
    }
    else if(Utility::isStringHasSpace(name))
    {
        std::cerr << "Error: spaces not allowed\n";
        return false;
    }
    else if(Common::isContainReservedWords(name))
    {
        return false;
    }
    else
    {
        return true;
    }
}
