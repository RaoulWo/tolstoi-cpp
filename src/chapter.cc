#include "chapter.h"

#include <iostream>
#include <numeric>

namespace Tolstoy
{

std::function<std::vector<std::string>(const std::vector<std::string>&)> Chapter::Tokenize = [](const std::vector<std::string>& lines)
{
    std::vector<std::vector<std::string>> tokenizedLines;
    tokenizedLines.reserve(lines.size());

    std::transform(lines.begin(), lines.end(), std::back_inserter(tokenizedLines), Chapter::TokenizeLine);

    return std::accumulate(tokenizedLines.begin(), tokenizedLines.end(), std::vector<std::string>{},
        [](const std::vector<std::string>& first, const std::vector<std::string>& last) {
        std::vector<std::string> result = first;
        result.insert(result.end(), last.begin(), last.end());
        return result;
    });
};

std::function<std::vector<std::string>(const std::string&)> Chapter::TokenizeLine = [](const std::string& line)
{
    std::vector<std::string> result;

    size_t initialPos = 0;
    size_t pos = line.find(' ');

    while (pos != std::string::npos)
    {
        std::string token = line.substr(initialPos, pos - initialPos);
        result.push_back(token);

        initialPos = pos + 1;
        pos = line.find(' ', initialPos);
    }
    result.push_back(line.substr(initialPos, std::min(pos, line.size()) - initialPos + 1));

    return result;
};

Chapter::Chapter(const std::vector<std::string>& lines)
{
    tokens_ = Chapter::Tokenize(lines);
}

} // Tolstoy