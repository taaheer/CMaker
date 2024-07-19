#ifndef CMAKE_H
#define CMAKE_H

#include <string>
#include <vector>

#include "Project.h"

constexpr std::string gFilename{"CMakeLists.txt"};

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
    std::string version{};
    const std::string defaultVersion{"3.7...3.29"};
    static constexpr double leastMinimumVersion{3.0};
    static constexpr double latestAvailableVersion{3.3};
    static constexpr std::array<std::string, 3> scopes{"INTERFACE", "PUBLIC", "PRIVATE"};
    Project project{};
    std::string executableName{};
    std::vector<std::string> fileSources{};
    std::vector<LibraryInfo> libraries{};
    std::string cppStandard{};

    std::string addHeaderComment() const;
    std::string addCMakePolicy() const;
    bool isCMakeVersionValid(const std::string& input) const;
    bool isLibraryTypeValid(const std::string &type, const std::array<std::string, 3> &types) const;
    bool isScopeValid(const std::string &scope) const;
    bool isCppStandardValid(const std::string &standard) const;
    void writingProject(std::ofstream &cmakeFile) const;

    void writeMinimumVersion(std::ofstream &cmakeFile) const;
    void settingProject();
    void settingExecutable(std::ofstream &cmakeFile);
    void settingLibrary(std::ofstream &cmakeFile);
    void targetIncludeDirectory(std::ofstream &cmakeFile);
    void linkLibraryies(std::ofstream &cmakeFile);
    void setCppStandard(std::ofstream &cmakeFile);

    std::string getLibraryNameFromUser();
    std::string getLibraryTypeFromUser();
    std::string getLibrarySourceFromUser(const LibraryInfo &library);

    void setVersion();
    void setExecutableName();
    void setFileSource();

    std::string getVersion() const;
    std::string getExecutableName() const;
    std::vector<std::string> getFileSource() const;

    public:
    
    void generateCMake([[maybe_unused]]std::size_t count);
    void removeCMake([[maybe_unused]]std::size_t count) const;
};

#endif
