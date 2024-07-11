#ifndef CMAKE_H
#define CMAKE_H

#include <string>

constexpr std::string gFilename{"CMakeLists.txt"};

class CMake
{
    private:
    std::string defaultVersion{"3.7...3.29"};
    const double leastMinimumVersion{3.0};
    const double latestAvailableVersion{3.3};

    std::string addHeader() const;
    std::string setCMakeVersion() const;
    bool isCMakeVersionValid(const std::string& input) const;

    public:
    
    void generateCMake([[maybe_unused]]std::size_t count) const;
    void removeCMake([[maybe_unused]]std::size_t count) const;
};

#endif
