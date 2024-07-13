#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <set>

class Project
{
    private:
    std::string projectName{};
    std::string projectVersion{};
    std::string projectDescription{};

    bool isProjectNameValid(const std::string& name) const;
    bool isStringHasSpace(const std::string& name) const;
    bool isContainReservedWords(const std::string& name) const;
    std::set<std::string> getReservedListOf(const std::string &argument) const;


    public:

    void setName();
    std::string setProjectName() const;
    std::string setProjectVersion() const;
    std::string setProjectDescription() const;

    std::string getName() const;
};

#endif
