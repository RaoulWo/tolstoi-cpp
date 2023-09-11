#ifndef TOLSTOY_SRC_BOOK_H_
#define TOLSTOY_SRC_BOOK_H_

#include "file_reader.h"
#include "chapter.h"
#include "terms.h"

#include <functional>
#include <string>
#include <vector>

namespace Tolstoy
{

class Book
{
public:
    Book(const FileContents& contents);

    static std::function<bool(const std::string&)> StartsChapter;
    static std::function<bool(const std::string&)> Starts;
    static std::function<bool(const std::string&)> Ends;

    static std::function<std::vector<Chapter>(const std::vector<std::string>&)> Chapterize;

    inline std::vector<Chapter> chapters() const { return chapters_; }
    inline Terms peace() const { return peace_; }
    inline Terms war() const { return war_; }

private:
    std::vector<Chapter> chapters_;

    Terms peace_;
    Terms war_;
};

} // Tolstoy

#endif // TOLSTOY_SRC_BOOK_H_