#ifndef CMAKE_H
#define CMAKE_H

#include <string>

#include "Project.h"

constexpr std::string gFilename{"CMakeLists.txt"};

class CMake
{
    private:
    std::string version{};
    const std::string defaultVersion{"3.7...3.29"};
    static constexpr double leastMinimumVersion{3.0};
    static constexpr double latestAvailableVersion{3.3};

    std::string addHeaderComment() const;
    std::string addCMakePolicy() const;
    bool isCMakeVersionValid(const std::string& input) const;
    void writeMinimumVersion(std::ofstream &cmakeFile) const;
    void settingProject(std::ofstream &cmakeFile, const Project &project) const;

    void setVersion();

    std::string getVersion() const;

    public:
    
    void generateCMake([[maybe_unused]]std::size_t count);
    void removeCMake([[maybe_unused]]std::size_t count) const;
};

#endif
