#include "book.h"
#include "util.h"
#include <sstream>

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author)
  : Product(category, name, price, qty), isbn_(isbn), author_(author) {
}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> words;

    std::set<std::string> nameWords = parseStringToWords(name_);
    std::set<std::string> authorWords = parseStringToWords(author_);

    std::set<std::string>::iterator it;

    for(it = nameWords.begin(); it != nameWords.end(); ++it) {
        words.insert(*it);
    }

    for(it = authorWords.begin(); it != authorWords.end(); ++it) {
        words.insert(*it);
    }

    words.insert(isbn_);

    return words;
}

std::string Book::displayString() const
{
    std::ostringstream oss;

    oss << name_ << "\n";
    oss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
    oss << price_ << " " << qty_ << " left.";

    return oss.str();
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n";
    os << name_ << "\n";
    os << price_ << "\n";
    os << qty_ << "\n";
    os << isbn_ << "\n";
    os << author_ << "\n";
}

