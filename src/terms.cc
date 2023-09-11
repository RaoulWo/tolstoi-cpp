#include "terms.h"

#include "utils.h"

#include <sstream>

namespace Tolstoy
{

std::function<std::string(const Terms&)> Terms::ToString = [](const Terms& terms)
{
    std::stringstream result;

    for (const auto& token : terms.tokens())
        result << token << '\n';

    return result.str();
};

Terms::Terms(const std::vector<std::string>& lines)
{
    std::transform(lines.begin(), lines.end(), std::back_inserter(tokens_), trim);
}

std::ostream& operator<< (std::ostream& stream, const Terms& terms)
{
    stream << Terms::ToString(terms);
    return stream;
}

} // Tolstoy
