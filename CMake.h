#ifndef CMAKE_H
#define CMAKE_H

#include <string>

constexpr std::string gFilename{"CMakeLists.txt"};

class CMake
{
    private:
    std::string version{};
    const std::string defaultVersion{"3.7...3.29"};
    static const double leastMinimumVersion{3.0};
    static const double latestAvailableVersion{3.3};

    std::string addHeader() const;
    void setVersion();
    bool isCMakeVersionValid(const std::string& input) const;

    std::string getVersion() const;

    public:
    
    void generateCMake([[maybe_unused]]std::size_t count);
    void removeCMake([[maybe_unused]]std::size_t count) const;
};

#endif
