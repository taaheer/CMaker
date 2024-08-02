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

// Ask CMake version until its valid
std::string CMake::getCMakeVersionFromUser(const std::string &message)
{
    std::string version{};
    do
    {
        std::cout << message;
        std::getline(std::cin, version);
    }
    while(!isCMakeVersionValid(version));

    return version;
}

void CMake::settingPolicyByCMakeVersion(std::ofstream &cmakeFile)
{
    std::string version{getCMakeVersionFromUser("Enter Minimum version for Policy (enter to set " + getCMakeRequiredVersion() + "): ")};
    std::string maxVersion{};
    
    if(!minimumRequiredVersion.empty() || !version.empty())
    {
        maxVersion = getCMakeVersionFromUser("Enter the policy_max (enter to skip):");
    }

    cmake_policy(cmakeFile, version, maxVersion);

}

// Write cmake_policy(VERSION <version>)
// or cmake_policy(VERSION <version>...<max>)
void CMake::cmake_policy(std::ofstream &cmakeFile, const std::string &version, const std::string &maxVersion)
{
    cmakeFile << "cmake_policy(VERSION ";

    if(!version.empty())
    {
        cmakeFile << version;
    }
    else
    {
        cmakeFile << getCMakeRequiredVersion();
    }

    if(!minimumRequiredVersion.empty() || !version.empty())
    {
        if(!maxVersion.empty())
        {
            cmakeFile << "..." << maxVersion;
        }
    }

    cmakeFile << ")\n\n";
}

// Ask user for CMake policy CMP<index>
std::vector<Policy> CMake::getPoliciesFromUser()
{
    std::vector<Policy> policies{};

    while(true)
    {
        Policy policy;
        std::cout << "Enter index number (enter to exit): CMP";
        getline(std::cin, policy.integerIndex);

        if(policy.integerIndex.empty())
        {
            break;
        }

        if(!Utility::isStringNumeric(policy.integerIndex))
        {
            std::cerr << "Error: its not an integer\n";
            continue;
        }

        int integerIndex{std::stoi(policy.integerIndex)};

        if(integerIndex >= 0 && integerIndex <= 170)
        {
            std::string newOld{};
            while(true)
            {
                std::cout << "OLD|NEW (o/n): ";
                std::getline(std::cin, newOld);

                if(newOld.empty())
                {
                    std::cerr << "Error: input was empty\n";
                    continue; 
                }

                newOld = Utility::toLowerCase(newOld);

                if(newOld == "o" || newOld == "old")
                {
                    policy.newOld = true;
                    break;
                }
                else if(newOld == "n" || newOld == "new")
                {
                    policy.newOld = false;
                    break;
                }
                else
                {
                    std::cerr << "Error: wrong input\n";
                }
            }

            policies.push_back(policy);
        }
    }

    return policies;
}

void CMake::settingPolicyExplicitly(std::ofstream &cmakeFile)
{
    std::vector<Policy> policies{getPoliciesFromUser()};

    cmake_policy(cmakeFile, policies);
}

// Write cmake_policy(SET CMP<index> <OLD|NEW>)
void CMake::cmake_policy(std::ofstream &cmakeFile, const std::vector<Policy> &policies)
{
    for(const Policy &policy : policies)
    {
        cmakeFile << "cmake_policy(SET CMP" << Utility::getStringDigitLengthOf(4, policy.integerIndex) << ' ';
        if(policy.newOld)
        {
            cmakeFile << "OLD";
        }
        else
        {
            cmakeFile << "NEW";
        }
        cmakeFile << ")\n";
    }

    cmakeFile << '\n';
}

// Todo
// Not implement because no idea how to implement
void CMake::settingPolicyStack()
{
    std::cerr << "Note: this feature not implemented because I have no idea how should I implement this\n";
}

void CMake::cmakeMinimumRequired(std::ofstream &cmakeFile)
{
    minimumRequiredVersion = getCMakeVersionFromUser("Enter Minimum required version of CMake (skip to set " + defaultMinimumRequiredVersion + " as default): ");

    std::string policyMax{};

    if(!minimumRequiredVersion.empty())
    {

        policyMax = getCMakeVersionFromUser("Enter the policy_max (enter to skip):");
    }

    cmake_minimum_required(cmakeFile, policyMax);
}

// Write cmake_minimun_required(VERSION <version>)
// or cmake_minimum_required(VERSION <version>...<max>)
void CMake::cmake_minimum_required(std::ofstream &cmakeFile, const std::string &policyMax)
{
    cmakeFile << "cmake_minimum_required(VERSION ";
    if(!minimumRequiredVersion.empty())
    {
        cmakeFile << minimumRequiredVersion;

        if(!policyMax.empty())
        {
            cmakeFile << "..." << policyMax;
        }
    }
    else
    {
        cmakeFile << defaultMinimumRequiredVersion;
    }

    cmakeFile << ")\n\n";
}

void CMake::cmakePolicySetOptions(std::ofstream &cmakeFile)
{
    bool isValid{false};

    const std::array<std::string, 3> options{"Setting Policies by CMake Version", "Setting Policies Explicitly", "CMake Policy Stack"};
    
    while(!isValid)
    {
        std::string option{promptWithOption(options, "select CMake policy setting (enter to skip):", true)};

        if(option.empty())
        {
            isValid = true;
            break;
        }

        int optionNumber{std::stoi(option)};

        switch (optionNumber)
        {
        case 0:
            settingPolicyByCMakeVersion(cmakeFile);
            break;
        case 1:
            settingPolicyExplicitly(cmakeFile);
            break;
        case 2:
            settingPolicyStack();
            break;
        
        default:
            break;
        }
    }
}

std::string CMake::getCMakeRequiredVersion() const
{
    if(!minimumRequiredVersion.empty())
    {
        return minimumRequiredVersion;
    }

    return defaultMinimumRequiredVersion;
}

// Add comment that it was generated by CMake
std::string CMake::addHeaderComment() const
{
    return "# This was generated by CMaker https://github.com/taaheer/CMaker\n"
    "# With modern pratice and suggestion from https://cliutils.gitlab.io/modern-cmake/\n\n";
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

std::vector<std::string> CMake::getFilesSourcesFromUser()
{
    std::vector<std::string> sources{};
    std::string source{};
    bool isValid{false};
    std::string added{};

    while(!isValid)
    {
        if(!source.empty())
        {
            std::cout << "added" << '(' << sources.size() << "):" << added << '\n';
        }
        std::cout << "Enter file sources (enter to skip): ";
        std::getline(std::cin, source);

        if(source.empty())
        {
            if(sources.empty())
            {
                std::cerr << "Note: New in version 3.11: The source files can be omitted if they are added later using target_sources().\n";
                isValid = true;
            }
            else
            {
                isValid = true;
            }
        }
        else if(Utility::isSourceExist(source))
        {
            sources.push_back(source);
            added += ' ' + source;
        }
        else
        {
            std::cerr << "Error: " << source << " does not exist\n";
        }
    }

    return sources;
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

std::string CMake::getExecutableNameFromUser()
{
    std::string name{};

    do
    {
        std::cout << "Enter executable name (Enter to set " << project.getName() << " as executable name): ";
        std::getline(std::cin, name);
    }
    while(!Common::isNameValid(name, true));

    return name;
}

bool CMake::setGlobalFromUser()
{
    std::string input{};
    bool isGlobal{};

    while(true)
    {
        std::cout << "Set global? (y/n): ";
        std::getline(std::cin, input);

        if(input.empty())
        {
            std::cerr << "Error: input was empty\n";
            continue; 
        }

        input = Utility::toLowerCase(input);

        if(input == "y" || input == "yes")
        {
            isGlobal = true;
            break;
        }
        else if(input == "n" || input == "no")
        {
            isGlobal = false;
            break;
        }
        else
        {
            std::cerr << "Error: wrong input\n";
        }
    }

    return isGlobal;
}

std::string CMake::getExecutableOptionFromUser()
{
    std::array<std::string, 3> options{"WIN32_EXECUTABLE", "MACOSX_BUNDLE", "EXCLUDE_FROM_ALL"};

    std::string option{promptWithOption(options, "Choose an option (enter to skip): ", true)};

    if(!option.empty())
    {
        return Utility::getCorrespondingElementFromString(option, options); 
    }
    else
    {
        return {};
    }

}

std::string CMake::getCXXStandardFromUser()
{
    std::string standard{};

    do
    {
        std::cout << "Enter C++ standard (e.g. 23): ";
        std::getline(std::cin, standard);
    }
    while(!isCppStandardValid(standard));

    return standard;
}

bool CMake::isCXXStandardRequiredFromUser()
{
    std::string input{};
    while(true)
    {
        std::cout << "set " << cxxStandard << " as required (y/n): ";
        std::getline(std::cin, input);

        std::string lowerCase{Utility::toLowerCase(input)};

        if(input.empty())
        {
            std::cerr << "Setting " << cxxStandard << " as required\n";
            return true;
        } 

        if(lowerCase == "y" || lowerCase == "yes")
        {
            return true;
        }
        else if(lowerCase == "n" || lowerCase == "no")
        {
            return false;
        }
    }
}

void CMake::set(std::ofstream &cmakeFile, std::string variable, std::string value)
{
    cmakeFile << "set(" << variable << ' ' << value << ")\n";
}

void CMake::normalExecutable(std::ofstream &cmakeFile)
{
    executableName = getExecutableNameFromUser();
    std::string option{getExecutableOptionFromUser()};
    std::vector<std::string> sources{getFilesSourcesFromUser()};

    add_executable(cmakeFile, getExecutableName(), option, sources);
}

void CMake::add_executable(std::ofstream &cmakeFile, const std::string &name, const std::string &option, const std::vector<std::string> &sources)
{
    cmakeFile << "add_executable(" << name << ' ';

    if(!option.empty())
    {
        cmakeFile << option;
    }

    for(const std::string &source : sources)
    {
        cmakeFile << ' ' << source;
    }

    cmakeFile << ")\n";
}

void CMake::importedExecutable(std::ofstream &cmakeFile)
{
    executableName = getExecutableNameFromUser();
    bool isGlobal{setGlobalFromUser()};

    add_executable(cmakeFile, getExecutableName(), isGlobal);
}

void CMake::add_executable(std::ofstream &cmakeFile, const std::string &name, bool isGlobal)
{
    cmakeFile << "add_executable(" << name << " IMPORTED ";
    if(isGlobal)
    {
        cmakeFile << "GLOBAL";
    }
    cmakeFile << ")\n\n";
}

void CMake::settingCXXStandard(std::ofstream &cmakeFile)
{
    cxxStandard = getCXXStandardFromUser();
    bool required{isCXXStandardRequiredFromUser()};

    set(cmakeFile, "CMAKE_CXX_STANDARD", cxxStandard);

    if(required)
    {
        set(cmakeFile, "CMAKE_CXX_STANDARD_REQUIRED", "True");
    }
}

// Write project(<name> LANGUAGE <language>)
// optionally project(<name> VERSION <version> DESCRIPTION <description> HOMEPAGE_URL <url> LANGAUGE <language>)
void CMake::writeProject(std::ofstream &cmakeFile) const
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

    if(!project.getHomepageUrl().empty())
    {
        cmakeFile << " HOMEPAGE_URL \"" << project.getHomepageUrl() << "\"";
    }
            
    cmakeFile << " LANGUAGES " << project.getLanguage() <<")\n\n";
}

void CMake::settingExecutable(std::ofstream &cmakeFile)
{
    bool isValid{false};

    const std::array<std::string, 2> options{"Normal Executable", "Imported Executable"};
    bool isNameSet{false};
    
    while(!isValid)
    {
        std::string option{promptWithOption(options, "select Executable type:", true)};

        if(option.empty() && !isNameSet)
        {
            std::cerr << "Error: executable name is required\n";
            continue;
        }
        else if(option.empty() && isNameSet)
        {
            isValid = true;
            break;
        }

        int optionNumber{std::stoi(option)};

        switch (optionNumber)
        {
        case 0:
            normalExecutable(cmakeFile);
            isNameSet = true;
            break;
        case 1:
            importedExecutable(cmakeFile);
            isNameSet = true;
            break;
        
        default:
            break;
        }
    }
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

bool CMake::isLibraryTypeValid(const std::string &type, const std::array<std::string, 3> &types) const
{
    if(type.empty())
    {
        return true;
    }
    else if(Utility::isStringNumeric(type))
    {
        return Utility::isNumericStringInRange(type, types.size());
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
        return Utility::isNumericStringInRange(scope, scopes.size());
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
    if(standard.empty())
    {
        std::cerr << "Error: No input was given\n";
        return false;
    }

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

void CMake::settingProject(std::ofstream &cmakeFile)
{
    project.setName();
    project.setVersion();
    project.setDescription();
    project.setHomageUrl();
    project.setLanguage();

    writeProject(cmakeFile);
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

    cmakeMinimumRequired(cmakeFile);
    cmakePolicySetOptions(cmakeFile);

    settingProject(cmakeFile);


    // These to dependent of settingProject()
    settingExecutable(cmakeFile);

    if(project.getLanguage() == "CXX")
    {
        settingCXXStandard(cmakeFile);
    }

    cmakeFile.close();

    // refactor
    settingLibrary(cmakeFile);

    if(!libraries.empty())
    {
        targetIncludeDirectory(cmakeFile);
        linkLibraryies(cmakeFile);
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
