#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn)
  : Product(category, name, price, qty), // this part constructs all of products' members
  author_(author), 
  isbn_(isbn)
{

}

Book::~Book()
{
  // honestly I'll deal with destructors after mydatastore is done

}

set<string> Book::keywords() const {
     // defining keywords and actual words for containing the strings
    set<string> authorSet = parseStringToWords(convToLower(author_));
    set<string> nameSet = parseStringToWords(convToLower(name_));
    set<string> mySet = setUnion(authorSet, nameSet);

    mySet.insert(isbn_);

    return mySet;
}

string Book::displayString() const {
  stringstream ss;
  ss << setprecision(2) << price_;

  string result = name_ + "\n";
  result += "Author: " + author_ + " ISBN: " + isbn_ + "\n";
  result += to_string(price_) + "\n" + to_string(qty_) + " left.";

  return result;
}

void Book::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

// indexing for 0 and 1 in function tbd...

// it honestly might be extra for members

// I think so


