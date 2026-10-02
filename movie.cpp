#include "movie.h"
#include "util.h"
#include <sstream>

Movie::Movie(const std::string category,
             const std::string name,
             double price,
             int qty,
             const std::string genre,
             const std::string rating)
    : Product(category, name, price, qty),
      genre_(genre),
      rating_(rating)
{
}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> words;

    std::set<std::string> nameWords = parseStringToWords(name_);

    std::set<std::string>::iterator it;

    for(it = nameWords.begin(); it != nameWords.end(); ++it) {
        words.insert(*it);
    }

    words.insert(genre_);

    return words;
}

std::string Movie::displayString() const
{
    std::ostringstream oss;

    oss << name_ << "\n";
    oss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    oss << price_ << " " << qty_ << " left.";

    return oss.str();
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n";
    os << name_ << "\n";
    os << price_ << "\n";
    os << qty_ << "\n";
    os << genre_ << "\n";
    os << rating_ << "\n";
}