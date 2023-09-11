#ifndef TOLSTOY_SRC_PARSER_H_
#define TOLSTOY_SRC_PARSER_H_

#include <functional>
#include <getopt.h>
#include <string>

namespace Tolstoy
{

const option kOptions[] = {
    {"book", required_argument, 0, 'b'},
    {"peace", required_argument, 0, 'p'},
    {"war", required_argument, 0, 'w'},
    {0, 0, 0, 0} // Sentinel
};

class CommandLineArguments
{
public:
    CommandLineArguments(std::string bookFilePath, std::string peaceFilePath, std::string warFilePath)
        : book_file_path_(bookFilePath), peace_file_path_(peaceFilePath), war_file_path_(warFilePath) {}

    static std::function<bool(const CommandLineArguments&)> AreValid;

    inline std::string book_file_path() const { return book_file_path_; }
    inline std::string peace_file_path() const { return peace_file_path_; }
    inline std::string war_file_path() const { return war_file_path_; }

private:
    std::string book_file_path_;
    std::string peace_file_path_;
    std::string war_file_path_;
};

class Parser
{
public:
    static std::function<CommandLineArguments(const int, char* const*)> Parse;
};

} // Tolstoy

#endif // TOLSTOY_SRC_PARSER_H_