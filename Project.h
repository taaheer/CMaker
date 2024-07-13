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

    bool isProjectNameValid() const;
    bool isContainReservedWords() const;
    std::set<std::string> getReservedListOf(const std::string &argument) const;


    public:

    void setName();
    void setVersion();
    void setDescription();

    std::string getName() const;
    std::string getVersion() const;
    std::string getDescription() const;
};

#endif
