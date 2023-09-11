#ifndef TOLSTOY_SRC_UTILS_H_
#define TOLSTOY_SRC_UTILS_H_

#include <functional>
#include <numeric>
#include <string>

namespace Tolstoy
{

class Utils
{
public:
    static std::function<std::string(const std::vector<std::string>&)> Concatenate;
    static std::function<std::string(const std::string&)> Trim;
    static std::function<bool(const std::string&)> IsNonWhiteSpaceString;
    static std::function<std::vector<std::string>(const std::vector<std::string>&)> FilterNonWhiteSpaceStrings;
    static std::function<bool(const char)> IsValidChar;
    static std::function<std::string(const std::string&)> StripToken;
    static std::function<std::vector<std::string>(const std::vector<std::string>&)> Strip;

private:
    static std::function<std::string(const std::string&)> TrimLeft;
    static std::function<std::string(const std::string&)> TrimRight;
};

} // Tolstoy

#endif // TOLSTOY_SRC_UTILS_H_