#include "utils.h"

#include <iostream>

namespace Tolstoy
{

std::function<std::string(const std::vector<std::string>&)> Utils::Concatenate = [](const std::vector<std::string>& v)
{
    return std::accumulate(v.begin(), v.end(), std::string(), [](const std::string& left, const std::string& right) {
        std::cout << left + right;
        return left + right;
    });
};

std::function<std::string(const std::string&)> Utils::Trim = [](const std::string& s)
{
    return Utils::TrimLeft(Utils::TrimRight(s));
};

std::function<std::string(const std::string&)> Utils::TrimLeft = [](const std::string& s)
{
    std::string result = s;
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char c) {
        return !std::isspace(c);
    }));
    return result;
};

std::function<std::string(const std::string&)> Utils::TrimRight = [](const std::string& s)
{
    std::string result = s;
    result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char c) {
        return !std::isspace(c);
    }).base(), result.end());
    return result;
};

} // Tolstoy