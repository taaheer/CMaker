#ifndef CMAKE_H
#define CMAKE_H

#include <string>
#include <vector>

#include "Project.h"
#include "Utility.h"

constexpr std::string gFilename{"CMakeLists.txt"};

struct Policy
{
    std::string integerIndex{};
    bool newOld{};
};

struct LibraryInfo
{
    std::string name{};
    std::string type{};
    std::vector<std::string> source{};
    std::string scope{};
    std::string directory{};
};

class CMake
{
    private:
    std::string minimumRequiredVersion{};
    const std::string defaultMinimumRequiredVersion{"3.7...3.29"};
    static constexpr double leastMinimumVersion{3.0};
    static constexpr double latestAvailableVersion{3.3};
    Project project{};
    std::string executableName{};
    std::string cxxStandard{};

    // refactor

    static constexpr std::array<std::string, 3> scopes{"INTERFACE", "PUBLIC", "PRIVATE"};
    std::vector<LibraryInfo> libraries{};

    // helper function

    std::string getCMakeVersionFromUser(const std::string &message);
    std::vector<Policy> getPoliciesFromUser();
    bool isCMakeVersionValid(const std::string& input) const;
    std::string getExecutableNameFromUser();
    bool setGlobalFromUser();
    std::string getExecutableOptionFromUser();
    std::string getCXXStandardFromUser();
    bool isCXXStandardRequiredFromUser();
    bool isCppStandardValid(const std::string &standard) const;
    void set(std::ofstream &cmakeFile, std::string variable, std::string value);
    std::string getVariableFromUser();

    // prompt user with messsasge and option and ask for input, then verify that input with flag to set whether empty input is vaid input
    template <typename T, std::size_t N>
    std::string promptWithOption(const std::array<T, N> &options, const std::string &message, bool isEmptyEnterValid = false)
    {
        std::string option{};

        std::size_t size{options.size()};
        bool isValid{false};

        while(!isValid)
        {
            std::cout << message << '\n';
            for(std::size_t i{}; i < size; ++i)
            {
                std::cout << i << ". " << options[i] << '\n';
            }
            std::cout << "Enter the number of your choice (0-" << size - 1 << "): "; 
            std::getline(std::cin, option);

            // user skip
            if(option.empty())
            {
                isValid = isEmptyEnterValid;
                if(!isEmptyEnterValid)
                {
                    std::cerr << "Error: input cannot be empty\n";
                }
            }
            else if(!Utility::isStringNumeric(option))
            {
                std::cerr << "Error: wrong input\n";
                continue;
            }
            else if(!Utility::isNumericStringInRange(option, options.size()))
            {
                std::cerr << "Error: wrong option\n";
                continue;
            }
            else
            {
                isValid = true;
            }
        }

        return option;
    }
        
    // main sets of functions
    
    std::string addHeaderComment() const;

    void cmakeMinimumRequired(std::ofstream &cmakeFile);
    void cmake_minimum_required(std::ofstream &cmakeFile, const std::string &policyMax);
    
    void cmakePolicySetOptions(std::ofstream &cmakeFile);
    
    void settingPolicyByCMakeVersion(std::ofstream &cmakeFile);

    void settingPolicyExplicitly(std::ofstream &cmakeFile);
    
    void cmake_policy(std::ofstream &cmakeFile, const std::string &version, const std::string &maxVersion);
    void cmake_policy(std::ofstream &cmakeFile, const std::vector<Policy> &policies);

    void settingPolicyStack();

    void settingProject(std::ofstream &cmakeFile);
    void writeProject(std::ofstream &cmakeFile) const;

    void settingExecutable(std::ofstream &cmakeFile);

    void normalExecutable(std::ofstream &cmake);
    void add_executable(std::ofstream &cmakeFile, const std::string &name, const std::string &option, const std::vector<std::string> &sources);
    
    void importedExecutable(std::ofstream &cmakeFile);
    void add_executable(std::ofstream &cmakeFile, const std::string &name, bool isGlobal);

    void settingCXXStandard(std::ofstream &cmakeFile);
    // getters
    
    std::string getCMakeRequiredVersion() const;
    std::string getExecutableName() const;

    // need to refactor

    bool isLibraryTypeValid(const std::string &type, const std::array<std::string, 3> &types) const;
    bool isScopeValid(const std::string &scope) const;

    void settingLibrary(std::ofstream &cmakeFile);
    void targetIncludeDirectory(std::ofstream &cmakeFile);
    void linkLibraryies(std::ofstream &cmakeFile);
    void setCppStandard(std::ofstream &cmakeFile);

    std::string getLibraryNameFromUser();
    std::string getLibraryTypeFromUser();
    std::string getLibrarySourceFromUser(const LibraryInfo &library);

    void setExecutableName();
    std::vector<std::string> getFilesSourcesFromUser();

    public:
    
    void generateCMake([[maybe_unused]]std::size_t count);
    void removeCMake([[maybe_unused]]std::size_t count) const;
};

#endif
