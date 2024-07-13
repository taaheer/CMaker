#include "Project.h"

#include "Utility.h"

#include <set> // for std::sets
#include <iostream> // for input and output
#include <string> // for string 

bool Project::isProjectNameValid() const
{
    if(name.empty())
    {
        return false;
    }
    else if(Utility::isStringHasSpace(name))
    {
        std::cerr << "Error: spaces not allowed\n";
        return false;
    }
    else if(isContainReservedWords())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Project::isContainReservedWords() const
{
    std::array<std::string, 3> cmakeListCommands{"cmake --help-command-list", "cmake --help-variable-list", "cmake --help-property-list"};

    // CppCheck is advicing to use std::any_of but when using std::any_of and lambda, it became slower and take more than with current code
    for(const std::string &command : cmakeListCommands)
    {
        static const std::set<std::string> listOfReservedCommand{getReservedListOf(command)};
        
        if(listOfReservedCommand.find(name) != listOfReservedCommand.end())
        {
            std::cerr << "Error: " << name << " is a reserved word\n";
            return true;
        }
    }

    return false;
}

std::set<std::string> Project::getReservedListOf(const std::string &argument) const
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

void Project::setName()
{
    do
    {
        std::cout << "Please enter project name: ";
        std::getline(std::cin, name);
    }
    while(!isProjectNameValid());
}

void Project::setVersion()
{
    do
    {
        std::cout << "Enter Project Version: ";
        std::getline(std::cin, version);
    }
    while(!Utility::isStringNumeric(version));
}

void Project::setDescription()
{
    std::cout << "Enter Project description:";
    std::getline(std::cin, description);
}

std::string Project::getName() const
{
    return name;
}

std::string Project::getVersion() const
{
    return version;
}

std::string Project::getDescription() const
{
    return description;
}
