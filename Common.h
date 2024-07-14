#ifndef COMMON_H
#define COMMON_H

#include <set>
#include <string>

namespace Common
{
    bool isContainReservedWords(const std::string &str);
    std::set<std::string> getReservedListOf(const std::string &argument);
}

#endif
