#include <iostream>

#include "file_reader.h"
#include "parser.h"

int main(int argc, char** argv)
{
    // Parse the command line arguments.
    Tolstoy::CommandLineArguments arguments = Tolstoy::Parser::Parse(argc, argv);
    if (!Tolstoy::CommandLineArguments::AreValid(arguments))
    {
        std::cout << "[ERROR] Usage: " << argv[0] << " --book <book-file-path> --peace <peace-file-path> --war <war-file-path>" << std::endl;

        return EXIT_FAILURE;
    }

    // Read the file contents.
    Tolstoy::FileContents contents = Tolstoy::FileReader::ReadFiles(arguments);
    if (!Tolstoy::FileContents::AreValid(contents))
    {
        std::cout << "[ERROR] One or more files could not be opened." << std::endl;

        return EXIT_FAILURE;
    }
}