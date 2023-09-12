#include "token.h"

#include <sstream>

namespace Tolstoy
{

std::function <std::vector<Token>(const std::vector<std::string>&)> Token::ToTokens = [](const std::vector<std::string>& strings)
{
    std::vector<Token> result;
    result.reserve(strings.size());

    for (long unsigned int i = 0; i < strings.size(); i++)
        result.push_back(Tolstoy::Token(i, strings[i]));

    return result;
};

std::function<std::string(const Token&)> Token::ToString = [](const Token& token)
{
    std::stringstream result;
    result << "[" << std::to_string(token.index()) << "]: " << token.content();
    return result.str();
};


std::ostream& operator<< (std::ostream& stream, const Token& token)
{
    stream << Token::ToString(token);
    return stream;
}

} // Tolstoy