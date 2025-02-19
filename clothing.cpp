#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "clothing.h"
#include "util.h"
//#include "product.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) 
  : Product(category, name, price, qty), brand_(brand), size_(size)
{


}

Clothing::~Clothing()
{
  
}

set<string> Clothing::keywords() const {
  set<string> nameSet = parseStringToWords(convToLower(name_));
  set<string> brandSet = parseStringToWords(convToLower(brand_));
  set<string> mySet = setUnion(nameSet, brandSet);

  return mySet;

}

string Clothing::displayString() const {
  stringstream ss;
  ss << setprecision(2) << price_;

  string result = name_ + "\n";
  result += "Size: " + size_ + " Brand: " + brand_ + "\n";
  result += to_string(price_) + "\n" + to_string(qty_) + " left.";

  return result;
}

void Clothing::dump(std::ostream& os) const {
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
