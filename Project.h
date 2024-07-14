#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <set>

class Project
{
    private:
    std::string name{};
    std::string version{};
    std::string description{};
    std::string language{};
    static constexpr std::array<std::string, 7> supportedLanguages{"C", "CXX", "Fortan", "ASM", "CUDA", "CSharp", "SWIFT"};


    bool isProjectNameValid() const;
    bool isLanguageSupported();


    public:

    void setName();
    void setVersion();
    void setDescription();
    void setLanguage();

    std::string getName() const;
    std::string getVersion() const;
    std::string getDescription() const;
    std::string getLanguage() const;
};

#endif
