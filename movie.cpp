#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) 
  : Product(category, name, price, qty), genre_(genre), rating_(rating)
{

}

Movie::~Movie()
{

}

set<string> Movie::keywords() const {
  string word; // defining keywords and actual words for containing the strings
  set<string> nameSet = parseStringToWords(convToLower(name_));
  set<string> ratingSet = parseStringToWords(convToLower(rating_));
  set<string> theSet = setUnion(nameSet, ratingSet);

  theSet.insert(convToLower(genre_));

  return theSet;
}

string Movie::displayString() const {
  stringstream ss;
  ss << setprecision(2) << price_;

  string result = name_ + "\n";
  result += "Genre: " + genre_ + " Rating: " + rating_ + "\n";
  result += to_string(price_) + "\n" + to_string(qty_) + " left.";

  return result;
}

void Movie::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}