#ifndef TOLSTOY_SRC_TERMS_H_
#define TOLSTOY_SRC_TERMS_H_

#include <functional>
#include <string>
#include <vector>

namespace Tolstoy
{

class Terms
{
public:
    Terms(const std::vector<std::string>& lines);

    static std::function<std::string(const Terms&)> ToString;

    inline std::vector<std::string> tokens() const { return tokens_; }

    friend std::ostream& operator<< (std::ostream& stream, const Terms& terms);
private:
    std::vector<std::string> tokens_;
};

} // Tolstoy

#endif // TOLSTOY_SRC_TERMS_H_
