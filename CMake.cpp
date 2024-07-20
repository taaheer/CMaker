#include "CMake.h"
#include "Project.h"

#include "Utility.h"
#include "Common.h"

#include <iostream>     // for input and output
#include <fstream>      // for creating file
#include <filesystem>   // for deleting file
#include <iostream>     // for input and output
#include <string>       // for strings and std::stod
#include <algorithm>    // for std::find

std::string CMake::addHeaderComment() const
{
    return "# This was generated by CMaker https://github.com/taaheer/CMaker\n"
    "# With modern pratice and suggestion from https://cliutils.gitlab.io/modern-cmake/\n\n";
}

void CMake::setVersion()
{
    do
    {
        std::cout << "Enter version (enter to set default): ";
        std::getline(std::cin, version);
    }
    while(!isCMakeVersionValid(version));
}

void CMake::setExecutableName()
{
    constexpr bool isEmptyEnterValid{true};
    do
    {
        std::cout << "Enter executable (enter project name as executable): ";
        std::getline(std::cin, executableName);
    }
    while(!Common::isNameValid(executableName, isEmptyEnterValid));
}

void CMake::setFileSource()
{
    std::string source{};
    bool isValid{false};

    while(!isValid)
    {
        std::cout << "Enter file sources (enter for next step): ";
        std::getline(std::cin, source);

        if(source.empty())
        {
            if(fileSources.empty())
            {
                std::cerr << "Error: need at least one source\n";
            }
            else
            {
                isValid = true;
            }
        }
        else if(Utility::isSourceExist(source))
        {
            fileSources.push_back(source);
        }
        else
        {
            std::cerr << "Error: " << source << " does not exist\n";
        }
    }
}

std::string CMake::addCMakePolicy() const
{
    std::string lessThanVersion{"3.12"};
    if(!version.empty())
    {
        lessThanVersion = version;
    }

    std::string policy{"if(${CMAKE_VERSION} VERSION_LESS " + lessThanVersion + ")\n"
    "\tcmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})\n"
    "endif()\n\n"};

    return policy;
}

bool CMake::isCMakeVersionValid(const std::string &input) const
{
    // user hit enter for default version
    if(input.empty())
    {
        return true;
    }
    else if(Utility::isStringNumeric(input))
    {
        const double inputVersion(std::stod(input));

        if(inputVersion < 0)
        {
            std::cerr << "Error: there is no negative version and never will be\n";
            return false;
        }
        else if(inputVersion < leastMinimumVersion)
        {
            std::cerr << "Warning: your chosen version is less than " << leastMinimumVersion 
            << " which is minimum for many modern practices, released in June 2014\n";
        }
        else if(inputVersion> latestAvailableVersion)
        {
            std::cerr << "Warning: either " << inputVersion << " does not exist yet, or my app is not updated.\n" 
            "Please check out https://cmake.org/download/ and raise and pull request if software is lagging behind\n";
        }

        return true;
    }
    else
    {
        std::cerr << "Error: wrong input, please enter correct minimum version\n";
        return false;
    }
}

void CMake::writeMinimumVersion(std::ofstream &cmakeFile) const
{
    cmakeFile << "cmake_minimum_required(VERSION " << getVersion() << ")\n\n";
    cmakeFile << addCMakePolicy();
}

void CMake::writingProject(std::ofstream &cmakeFile) const
{
    cmakeFile << "project(" << project.getName(); 

    if(!project.getVersion().empty())
    {
        cmakeFile << " VERSION " << project.getVersion();
    }

    if(!project.getDescription().empty())
    {
        cmakeFile << " DESCRIPTION \"" << project.getDescription() << "\"";
    }
            
    cmakeFile << " LANGUAGES " << project.getLanguage() <<")\n\n";
}

void CMake::settingExecutable(std::ofstream &cmakeFile)
{
    setExecutableName();
    setFileSource();

    cmakeFile << "add_executable( " << getExecutableName() << ' ';
    
    for(const std::string &source : getFileSource())
    {
        cmakeFile << source << ' ';
    }

    cmakeFile << ")\n\n";
}

void CMake::settingLibrary(std::ofstream &cmakeFile)
{
    LibraryInfo library{};

    while(true)
    {
        library.name = getLibraryNameFromUser();

        if(library.name.empty())
        {
            break;
        }

        library.type = getLibraryTypeFromUser();

        std::string source{};

        do
        {
            source = getLibrarySourceFromUser(library);

            if(!source.empty())
            {
                library.source.push_back(source);
            }
        }
        while(!source.empty());

        libraries.push_back(library);
    }

    for(const LibraryInfo &lib : libraries)
    {
        cmakeFile << "add_library( " << lib.name << ' ' << lib.type << ' '; 
        
        for(const std::string &source : lib.source)
        {
            cmakeFile << source << ' ';
        }
        cmakeFile << ")\n";
    }

    cmakeFile << "\n";
}

void CMake::targetIncludeDirectory(std::ofstream &cmakeFile)
{
    for(LibraryInfo &library : libraries)
    {
        do
        {
            std::cout << "scope of " << library.name << " ( ";
            for(const std::string &option : scopes)
            {
                std::cout << option << ' ';
            }
            std::cout << "): ";
            std::getline(std::cin, library.scope);
        }
        while(!isScopeValid(library.scope));

        if(Utility::isStringNumeric(library.scope))
        {
            library.scope = Utility::getCorrespondingElementFromString(library.scope, scopes);
        }

        do
        {
            std::cout << "directory of " << library.name<< ": ";
            std::getline(std::cin, library.directory);
        }
        while(!Utility::isSourceExist(library.directory));

        cmakeFile << "target_include_directories(" << library.name << ' ' << library.scope << ' ' << library.directory << ")\n";
    }

    cmakeFile << '\n';
}

void CMake::linkLibraryies(std::ofstream &cmakeFile)
{
    std::string target{};
    std::string scope{};

    for(const LibraryInfo &library : libraries)
    {
        do
        {
            std::cout << "Enter the target for " << library.name << " (enter to use executable name as target): ";
            std::getline(std::cin, target);
        }
        while(!Common::isNameValid(target, true));

        if(target.empty())
        {
            target = executableName;
        }

        do
        {
            std::cout << "link scope of " << library.name << " ( ";
            for(const std::string &option : scopes)
            {
                std::cout << option << ' ';
            }
            std::cout << "): ";
            std::getline(std::cin, scope);
        }
        while(!isScopeValid(library.scope));

        if(Utility::isStringNumeric(scope))
        {
            scope = Utility::getCorrespondingElementFromString(scope, scopes);
        }

        cmakeFile << "target_link_libraries(" << target << ' ' << scope << ' ' << library.name << ")\n";
    }
    cmakeFile << '\n';
}

void CMake::setCppStandard(std::ofstream &cmakeFile)
{
    do
    {
        std::cout << "Enter C++ standard: ";
        std::getline(std::cin, cppStandard);
    }
    while(!isCppStandardValid(cppStandard));

    cmakeFile << "set_property(TARGET " << getExecutableName() << " PROPERTY CXX_STANDARD " << cppStandard << ")\n\n";
}

bool CMake::isLibraryTypeValid(const std::string &type, const std::array<std::string, 3> &types) const
{
    if(type.empty())
    {
        return true;
    }
    else if(Utility::isStringNumeric(type))
    {
        return Utility::isNumericStringInRange(type, types);
    }
    else if(std::find(types.begin(), types.end(), type) != types.end())
    {
        return true;
    }

    std::cerr << "Error: does not recognise " << type << '\n';
    return false;
}

bool CMake::isScopeValid(const std::string &scope) const
{
    if(scope.empty())
    {
        std::cerr << "Error: scope is required\n";
        return false;
    }
    else if(Utility::isStringNumeric(scope))
    {
        return Utility::isNumericStringInRange(scope, scopes);
    }
    else if(std::find(scopes.begin(), scopes.end(), scope) != scopes.end())
    {
        return true;
    }

    std::cerr << "Error: does not recognise " << scope << '\n';
    return false;
}

bool CMake::isCppStandardValid(const std::string &standard) const
{
    if(Utility::isStringNumeric(standard))
    {
        int num{std::stoi(standard)};

        switch (num)
        {
            case 98:
            case 11:
            case 14:
            case 17:
            case 20:
            case 23:
                return true;
                break;
            
            case 26:
                std::cerr << "Warning: compiler may not support\n";
                return true;
                break;

            default:
                std::cerr << "Error: unsupported standard\n";
                return false;
                break;
        }
    }
    else
    {
        std::cerr << "Error: wrong input\n";
        return false;
    }
}

void CMake::settingProject()
{
    project.setName();
    project.setVersion();
    project.setDescription();
    project.setLanguage();
}

std::string CMake::getLibraryNameFromUser()
{
    std::string name{};
    constexpr bool isEmptyEnterValid{true};
    do
    {
        std::cout << "Enter library name (enter for next step): ";
        std::getline(std::cin, name);
    }
    while(!Common::isNameValid(name, isEmptyEnterValid));

    return name;
}

std::string CMake::getLibraryTypeFromUser()
{
    std::string type{};
    const std::array<std::string, 3> types{"STATIC", "SHARED", "MODULE"};

    do
    {
        std::cout << "Enter library type (enter for default) (type: ";
        for(const std::string &option : types)
        {
            std::cout << option << ' ';
        }
        std::cout << "): ";
        std::getline(std::cin, type);
    }
    while(!isLibraryTypeValid(type, types));

    if(type.empty())
    {
        return "";
    }
    else if(Utility::isStringNumeric(type))
    {
        int typeNumber{std::stoi(type)};

        return types[static_cast<std::size_t>(typeNumber)];
    }
    else
    {
        return type;
    }
}

std::string CMake::getLibrarySourceFromUser(const LibraryInfo &library)
{
    bool isSourceValid{false};

    std::string source{};
    while(!isSourceValid)
    {
        std::cout << "Enter the source: ";
        std::getline(std::cin, source);

        if(source.empty() && library.source.size() == 0)
        {
            std::cerr << "Error: need at least one source\n";
        }
        else if(source.empty() || Utility::isSourceExist(source) )
        {
            isSourceValid = true;
        }
        else
        {
            std::cerr << "Error: source does not exist\n";
        }
    }

    return source;
}

std::string CMake::getVersion() const
{
    if(version.empty())
    {
        return defaultVersion;
    }
    else
    {
        return version;
    }
}

std::string CMake::getExecutableName() const
{
    if(executableName.empty())
    {
        return project.getName();
    }
    else
    {
        return executableName;
    }
}

std::vector<std::string> CMake::getFileSource() const
{
    return fileSources;
}

void CMake::generateCMake([[maybe_unused]]std::size_t count)
{
    std::cout << "Generating " << gFilename << '\n';

    std::ofstream cmakeFile{gFilename};
    if(!cmakeFile.is_open())
    {
        std::cerr << "Failed to generate " << gFilename << '\n';
        return;
    }

    cmakeFile << addHeaderComment();

    setVersion();
    writeMinimumVersion(cmakeFile);
    settingProject();

    // These to dependent of settingProject()
    writingProject(cmakeFile);
    settingExecutable(cmakeFile);

    settingLibrary(cmakeFile);

    if(!libraries.empty())
    {
        targetIncludeDirectory(cmakeFile);
        linkLibraryies(cmakeFile);
    }

    if(project.getLanguage() == "CXX")
    {
        setCppStandard(cmakeFile);
    }

    cmakeFile.close();

    std::cout << gFilename << " generated successfully\n";
}

void CMake::removeCMake([[maybe_unused]]std::size_t count) const
{
    std::cout << "Removing " << gFilename << '\n';

    if(std::filesystem::exists(gFilename))
    {
        std::cout << gFilename << " found\n";

        if(std::filesystem::remove(gFilename))
        {
            std::cout << "Removed\n";
        }
        else
        {
            std::cerr << "Error removing\n";
        }
    }
    else
    {
        std::cerr << gFilename << " not found\n";
    }
}
