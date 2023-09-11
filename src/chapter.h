#ifndef TOLSTOY_SRC_CHAPTER_H_
#define TOLSTOY_SRC_CHAPTER_H_

#include "terms.h"

#include <functional>
#include <string>
#include <vector>

namespace Tolstoy
{

class Chapter
{
public:
    Chapter(const std::vector<std::string>& lines);

    static std::function<std::vector<std::string>(const std::vector<std::string>&)> Tokenize;
    static std::function<std::vector<std::string>(const std::string&)> TokenizeLine;

    static std::function <std::vector<std::string>(const Chapter&, const Terms&)> FilterByTerms;

    static std::function<int(const Chapter&)> WordCount;
    static std::function<int(const Chapter&, const Terms&)> TermCount;

    inline std::vector<std::string> tokens() const { return tokens_; }

private:
    std::vector<std::string> tokens_;
};

} // Tolstoy

#endif // TOLSTOY_SRC_CHAPTER_H_