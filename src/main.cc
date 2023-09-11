#include <iostream>

#include "book.h"

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

    Tolstoy::Book* book = new Tolstoy::Book(contents);

    int warCount = Tolstoy::Chapter::TermCount(book->chapters()[0], book->war());
    int peaceCount = Tolstoy::Chapter::TermCount(book->chapters()[0], book->peace());
    int wordCount = Tolstoy::Chapter::WordCount(book->chapters()[0]);

    std::cout << warCount << "\n";
    std::cout << peaceCount << "\n";
    std::cout << wordCount << "\n";

    delete book;
}