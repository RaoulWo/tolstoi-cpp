#include "book.h"

#include <iostream>
#include <memory>

// TODO Extract chapter lambdas into chapter static std::functions
// TODO Extract book lambdas into book static std::functions

// TERM COUNT
const auto chapter_term_count = [](const Tolstoy::Chapter& chapter, const Tolstoy::Terms& terms)
{
    return Tolstoy::Chapter::FilterByTerms(chapter, terms).size();
};
const auto book_peace_count = [](const Tolstoy::Book& book)
{
    std::vector<int> result;

    Tolstoy::Terms peace = book.peace();
    const auto chapter_peace_count = [&peace = std::as_const(peace)](const Tolstoy::Chapter& chapter)
    {
        return chapter_term_count(chapter, peace);
    };

    std::vector<Tolstoy::Chapter> chapters = book.chapters();
    std::transform(chapters.begin(), chapters.end(), std::back_inserter(result), chapter_peace_count);

    return result;
};
const auto book_war_count = [](const Tolstoy::Book& book)
{
    std::vector<int> result;

    Tolstoy::Terms war = book.war();
    const auto chapter_war_count = [&war = std::as_const(war)](const Tolstoy::Chapter& chapter)
    {
        return chapter_term_count(chapter, war);
    };

    std::vector<Tolstoy::Chapter> chapters = book.chapters();
    std::transform(chapters.begin(), chapters.end(), std::back_inserter(result), chapter_war_count);

    return result;
};

// NEAREST NEIGHBOUR DISTANCE
const auto sum_nearest_neighbour_distance = [](const std::vector<Tolstoy::Token>& tokens)
{
    if (tokens.size() <= 1) return 1;

    int sumDistance = 0;
    for (long unsigned int i = 0; i < tokens.size() - 1; i++)
    {
        sumDistance += (tokens[i + 1].index() - tokens[i].index());
    }

    return sumDistance;
};

// TERM DENSITY
const auto chapter_term_density = [](const Tolstoy::Chapter& chapter, const Tolstoy::Terms& terms)
{
    std::vector<Tolstoy::Token> tokens = Tolstoy::Chapter::FilterByTerms(chapter, terms);

    int sumDistance = sum_nearest_neighbour_distance(tokens);
    int term_count = chapter_term_count(chapter, terms);

    return sumDistance * term_count;
};
const auto book_peace_density = [](const Tolstoy::Book& book)
{
    std::vector<float> result;

    Tolstoy::Terms peace = book.peace();
    const auto chapter_peace_density = [&peace = std::as_const(peace)](const Tolstoy::Chapter& chapter)
    {
        return chapter_term_density(chapter, peace);
    };

    std::vector<Tolstoy::Chapter> chapters = book.chapters();
    std::transform(chapters.begin(), chapters.end(), std::back_inserter(result), chapter_peace_density);

    return result;
};
const auto book_war_density = [](const Tolstoy::Book& book)
{
    std::vector<float> result;

    Tolstoy::Terms war = book.war();
    const auto chapter_war_density = [&war = std::as_const(war)](const Tolstoy::Chapter& chapter)
    {
        return chapter_term_density(chapter, war);
    };

    std::vector<Tolstoy::Chapter> chapters = book.chapters();
    std::transform(chapters.begin(), chapters.end(), std::back_inserter(result), chapter_war_density);

    return result;
};

// DENSITY COMPARISON
const auto book_density_comparison = [](const Tolstoy::Book& book)
{
    std::vector<std::string> result;

    auto peace = book_peace_density(book);
    auto war = book_war_density(book);

    for (unsigned long int i = 0; i < peace.size(); i++)
    {
        std::string prefix = "[CHAPTER " + std::to_string(i + 1) + "]: ";
        if (peace[i] == war[i])
            result.push_back(prefix + "Equal density!");
        else if (peace[i] > war[i])
            result.push_back(prefix + "Peace related!");
        else
            result.push_back(prefix + "War related!");
    }

    return result;
};

int main(int argc, char** argv)
{
    // Parse the command line arguments.
    std::shared_ptr<Tolstoy::CommandLineArguments> arguments = std::make_shared<Tolstoy::CommandLineArguments>(Tolstoy::Parser::Parse(argc, argv));
    if (!Tolstoy::CommandLineArguments::AreValid(*arguments))
    {
        std::cout << "[ERROR] Usage: " << argv[0] << " --book <book-file-path> --peace <peace-file-path> --war <war-file-path>" << std::endl;

        return EXIT_FAILURE;
    }

    // Read the file contents.
    std::shared_ptr<Tolstoy::FileContents> contents = std::make_shared<Tolstoy::FileContents>(Tolstoy::FileReader::ReadFiles(*arguments));
    if (!Tolstoy::FileContents::AreValid(*contents))
    {
        std::cout << "[ERROR] One or more files could not be opened." << std::endl;

        return EXIT_FAILURE;
    }

    std::shared_ptr<Tolstoy::Book> book = std::make_shared<Tolstoy::Book>(*contents);
    std::shared_ptr<std::vector<std::string>> comparison = std::make_shared<std::vector<std::string>>(book_density_comparison(*book));

    for (const auto& s : (*comparison))
    {
        std::cout << s << '\n';
    }
}