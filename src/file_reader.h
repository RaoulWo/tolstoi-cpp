#ifndef TOLSTOY_SRC_FILE_READER_
#define TOLSTOY_SRC_FILE_READER_

#include "parser.h"

#include <functional>
#include <string>
#include <vector>

namespace Tolstoy
{

class FileContents
{
public:
    FileContents(std::vector<std::string> book, std::vector<std::string> peace, std::vector<std::string> war)
        : book_(book), peace_(peace), war_(war) {}

    static std::function<bool(const FileContents&)> AreValid;

    inline std::vector<std::string> book() const { return book_; }
    inline std::vector<std::string> peace() const { return peace_; }
    inline std::vector<std::string> war() const { return war_; }

private:
    std::vector<std::string> book_;
    std::vector<std::string> peace_;
    std::vector<std::string> war_;
};

class FileReader
{
public:
    static std::function<FileContents(const CommandLineArguments&)> ReadFiles;

private:
    static std::function<std::vector<std::string>(const std::string&)> ReadFile;
};

} // Tolstoy

#endif // TOLSTOY_SRC_FILE_READER_