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

std::function<bool(const std::string&)> Utils::IsNonWhiteSpaceString = [](const std::string& s)
{
    return std::none_of(s.begin(), s.end(), isspace);
};

std::function<std::vector<std::string>(const std::vector<std::string>&)> Utils::FilterNonWhiteSpaceStrings = [](const std::vector<std::string>& tokens)
{
    std::vector<std::string> result;
    std::copy_if(tokens.begin(), tokens.end(), std::back_inserter(result), Utils::IsNonWhiteSpaceString);
    return result;
};

std::function<bool(const char)> Utils::IsValidChar = [](const char c)
{
    return c != ';' && c != ':' && c != ',' && c != '.' && c != '(' && c != ')' && c != '\"' && c != '!' && c != '?' && c != '-' && c != '*';
};

std::function<std::string(const std::string&)> Utils::StripToken = [](const std::string& token)
{
    if (token.size() == 0) return token;

    std::string result = token;

    while (!Utils::IsValidChar(result[0])) result = result.substr(1, result.size() - 1);
    if (result.size() == 0) return result;
    while (!Utils::IsValidChar(result[result.size() - 1])) result = result.substr(0, result.size() - 1);

    return result;
};

std::function<std::vector<std::string>(const std::vector<std::string>&)> Utils::Strip = [](const std::vector<std::string>& tokens)
{
    std::vector<std::string> result;
    std::transform(tokens.begin(), tokens.end(), std::back_inserter(result), Utils::StripToken);
    return result;
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