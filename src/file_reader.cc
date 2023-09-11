#include "file_reader.h"

#include <fstream>

namespace Tolstoy
{

std::function<bool(const FileContents&)> FileContents::AreValid = [](const FileContents& contents)
{
    return !contents.book().empty() && !contents.peace().empty() && !contents.war().empty();
};

std::function<FileContents(const CommandLineArguments&)> FileReader::ReadFiles = [](const CommandLineArguments& args)
{
    auto book = Tolstoy::FileReader::ReadFile(args.book_file_path());
    auto peace = Tolstoy::FileReader::ReadFile(args.peace_file_path());
    auto war = Tolstoy::FileReader::ReadFile(args.war_file_path());

    return FileContents(book, peace, war);
};

std::function<std::vector<std::string>(const std::string&)> FileReader::ReadFile = [](const std::string& filePath)
{
    std::vector<std::string> result;
    std::fstream stream = std::fstream(filePath);

    if (stream.is_open())
    {
        std::string line;
        while (std::getline(stream, line))
            result.push_back(line);

        stream.close();
    }

    return result;
};

} // Tolstoy