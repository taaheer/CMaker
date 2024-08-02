#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <set>
#include <array>

class Project
{
    private:
    std::string name{};
    std::string version{};
    std::string description{};
    std::string homepageUrl{};
    std::string language{};
    static constexpr std::array<std::string, 15> supportedLanguages{"C", "CXX", "CSharp", "CUDA", "OBJC", "OBJCXX", "Fortran", "HIP", "ISPC", "Swift", "ASM", "ASM_NASM", "ASM_MARMASM", "ASM_MASM", "ASM_ATT"};

    bool isLanguageSupported();

    public:

    void setName();
    void setVersion();
    void setDescription();
    void setHomageUrl();
    void setLanguage();

    std::string getName() const;
    std::string getVersion() const;
    std::string getDescription() const;
    std::string getHomepageUrl() const;
    std::string getLanguage() const;
};

#endif
