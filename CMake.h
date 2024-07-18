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
    std::string source{};
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
    std::string executableName{};
    std::vector<std::string> fileSources{};
    std::vector<LibraryInfo> libraries{};

    std::string addHeaderComment() const;
    std::string addCMakePolicy() const;
    bool isCMakeVersionValid(const std::string& input) const;
    bool isLibraryTypeValid(const std::string &type, const std::array<std::string, 3> &types) const;
    bool isScopeValid(const std::string &scope, const std::array<std::string, 3> &scopes) const;
    void writingProject(std::ofstream &cmakeFile, const Project &project) const;

    void writeMinimumVersion(std::ofstream &cmakeFile) const;
    void settingProject(Project &project) const;
    void settingExecutable(std::ofstream &cmakeFile, const Project &project);
    void settingLibrary(std::ofstream &cmakeFile);
    void targetIncludeDirectory(std::ofstream &cmakeFile);

    std::string getLibraryNameFromUser();
    std::string getLibraryTypeFromUser();
    std::string getLibrarySourceFromUser();

    void setVersion();
    void setExecutableName();
    void setFileSource();

    std::string getVersion() const;
    std::string getExecutableName(const Project &project) const;
    std::vector<std::string> getFileSource() const;

    public:
    
    void generateCMake([[maybe_unused]]std::size_t count);
    void removeCMake([[maybe_unused]]std::size_t count) const;
};

#endif
