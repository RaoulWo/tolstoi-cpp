#include "parser.h"

namespace Tolstoy
{

std::function<CommandLineArguments(const int, char* const*)> Parser::Parse = [](const int argc, char* const* argv)
{
    std::string bookFilePath, peaceFilePath, warFilePath;
    int index = 0, option = 0;

    while ((option = getopt_long(argc, argv, "b:p:w:", kOptions, &index)) != -1)
    {
        switch (option)
        {
        case 'b':
            bookFilePath = optarg;
            break;
        case 'p':
            peaceFilePath = optarg;
            break;
        case 'w':
            warFilePath = optarg;
            break;
        }
    }

    return CommandLineArguments(bookFilePath, peaceFilePath, warFilePath);
};

std::function<bool(CommandLineArguments)> CommandLineArguments::AreValid = [](const CommandLineArguments& args) -> bool
{
    return !args.book_file_path().empty() && !args.peace_file_path().empty() && !args.war_file_path().empty();
};

} // Tolstoy