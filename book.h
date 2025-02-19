#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "product.h"

class Book : public Product {
public:
  Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn);
  ~Book();
   
  virtual std::set<std::string> keywords() const;

  virtual std::string displayString() const;

  virtual void dump(std::ostream& os) const;
   

  const std::string& getAuthor() const { return author_; }
  const std::string& getIsbn() const { return isbn_; }

protected:
  std::string author_;
  std::string isbn_;
};
#endif