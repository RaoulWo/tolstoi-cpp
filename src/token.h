#ifndef TOLSTOY_SRC_TOKEN_H_
#define TOLSTOY_SRC_TOKEN_H_

#include <functional>
#include <ostream>
#include <string>
#include <vector>

namespace Tolstoy
{

class Token
{
public:
    Token(int index, std::string content)
        : index_(index), content_(content) {}

    static std::function <std::vector<Token>(const std::vector<std::string>&)> ToTokens;

    static std::function<std::string(const Token&)> ToString;

    inline int index() const { return index_; }
    inline std::string content() const { return content_; }

    friend std::ostream& operator<< (std::ostream& stream, const Token& token);

private:
    int index_;
    std::string content_;
};

} // Tolstoy

#endif // TOLSTOY_SRC_TOKEN_H_