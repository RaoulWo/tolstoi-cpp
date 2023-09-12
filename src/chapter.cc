#include "chapter.h"

#include "utils.h"

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

std::function <std::vector<Token>(const Chapter&, const Terms&)> Chapter::FilterByTerms = [](const Chapter& chapter, const Terms& terms)
{
    std::vector<Token> result;
    std::vector<Token> chapterTokens = chapter.tokens();
    std::vector<std::string> termStrings = terms.tokens();

    std::copy_if(chapterTokens.begin(), chapterTokens.end(), std::back_inserter(result), [&](const Token& token) {
        return std::any_of(termStrings.begin(), termStrings.end(), [&](const std::string& t) {
            return t == token.content();
        });
    });

    return result;
};

std::function<int(const Chapter&)> Chapter::WordCount = [](const Chapter& chapter)
{
    return chapter.tokens().size();
};

Chapter::Chapter(const std::vector<std::string>& lines)
{
    // Tokenize the lines.
    auto tokenStrings = Chapter::Tokenize(lines);
    // Strip invalid beginning and trailing characters.
    tokenStrings = Utils::Strip(tokenStrings);
    // Filter only the non-whitespace tokens.
    tokenStrings = Utils::FilterNonWhiteSpaceStrings(tokenStrings);
    // Transform the token strings into token objects.
    tokens_ = Token::ToTokens(tokenStrings);
}

} // Tolstoy