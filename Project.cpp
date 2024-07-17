#include "Project.h"

#include "Utility.h"
#include "Common.h"

#include <set> // for std::sets
#include <iostream> // for input and output
#include <string> // for string 
#include <algorithm> // for std::find

bool Project::isLanguageSupported()
{
    if (std::find(supportedLanguages.begin(), supportedLanguages.end(), language) != supportedLanguages.end()) 
    {
        return true;
    } 
    else 
    {
        std::cerr << "Unsupported Language, please check the list of supported Languages\n";
        return false;
    }
}

void Project::setName()
{
    do
    {
        std::cout << "Please enter project name: ";
        std::getline(std::cin, name);
    }
    while(!Common::isNameValid(name));
}

void Project::setVersion()
{
    do
    {
        std::cout << "Enter Project Version (enter to skip): ";
        std::getline(std::cin, version);
    }
    while(!Utility::isStringNumeric(version));
}

void Project::setDescription()
{
    std::cout << "Enter Project description (enter to skip): ";
    std::getline(std::cin, description);
}

void Project::setLanguage()
{
    do
    {
        std::cout << "Enter the The language ( Supported are ";
        for(const std::string &supportedLanguage : supportedLanguages)
        {
            std::cout << supportedLanguage << ' ';
        }
        std::cout << ")\n";
        std::getline(std::cin, language);
    }
    while(!isLanguageSupported());
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

std::string Project::getLanguage() const
{
    return language;
}
