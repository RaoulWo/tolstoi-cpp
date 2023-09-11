#include <iostream>

#include "parser.h"

int main(int argc, char** argv)
{
    Tolstoy::CommandLineArguments arguments = Tolstoy::Parser::Parse(argc, argv);
    if (!Tolstoy::CommandLineArguments::AreValid(arguments))
    {
        std::cout << "Usage: " << argv[0] << " --book <book-file-path> --peace <peace-file-path> --war <war-file-path>" << std::endl;

        return EXIT_FAILURE;
    }
}