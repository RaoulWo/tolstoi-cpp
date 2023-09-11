#include "book.h"

#include "utils.h"

#include <iostream>

namespace Tolstoy
{

const std::string kChapterStart = "CHAPTER ";
const std::string kBookStart = "START OF THE PROJECT GUTENBERG EBOOK, WAR AND PEACE";
const std::string kBookEnd = "END OF THE PROJECT GUTENBERG EBOOK, WAR AND PEACE";

std::function<bool(const std::string&)> Book::StartsChapter = [](const std::string& line)
{
    return line.find(kChapterStart) != std::string::npos;
};

std::function<bool(const std::string&)> Book::Starts = [](const std::string& line)
{
    return line.find(kBookStart) != std::string::npos;
};

std::function<bool(const std::string&)> Book::Ends = [](const std::string& line)
{
    return line.find(kBookEnd) != std::string::npos;
};

std::function <std::vector<Chapter>(const std::vector<std::string>&)> Book::Chapterize = [](const std::vector<std::string>& lines)
{
    std::vector<std::vector<std::string>> chapters;

    for (const auto& line : lines)
    {
        if (Book::Ends(line)) break;

        if (Book::StartsChapter(line)) chapters.push_back({});

        if (!chapters.empty()) chapters.back().push_back(line);
    }

    std::vector<Chapter> result;
    std::transform(chapters.begin(), chapters.end(), std::back_inserter(result), [](const std::vector<std::string>& chapter) {
        return Chapter(chapter);
    });

    return result;
};

Book::Book(const FileContents& contents)
    : peace_(contents.peace()), war_(contents.war())
{
    chapters_ = Book::Chapterize(contents.book());
}

} // Tolstoy