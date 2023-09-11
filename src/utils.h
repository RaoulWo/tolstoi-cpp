#ifndef TOLSTOY_SRC_UTILS_H_
#define TOLSTOY_SRC_UTILS_H_

#include <functional>
#include <string>

namespace Tolstoy
{

const auto trim_left = [](const std::string& s) -> std::string
{
    std::string result = s;
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char c) {
        return !std::isspace(c);
    }));
    return result;
};

const auto trim_right = [](const std::string& s) -> std::string
{
    std::string result = s;
    result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char c) {
        return !std::isspace(c);
    }).base(), result.end());
    return result;
};

auto trim(const std::string& s) -> std::string
{
    return trim_left(trim_right(s));
}

} // Tolstoy

#endif // TOLSTOY_SRC_UTILS_H_