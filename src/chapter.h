#ifndef TOLSTOY_SRC_CHAPTER_H_
#define TOLSTOY_SRC_CHAPTER_H_

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

    inline std::vector<std::string> tokens() const { return tokens_; }

private:
    std::vector<std::string> tokens_;
};

} // Tolstoy

#endif // TOLSTOY_SRC_CHAPTER_H_