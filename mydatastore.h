#ifndef MY_DATASTORE_H
#define MY_DATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include <string>
#include "product.h"
#include "user.h"
#include "datastore.h"

class myDataStore : public DataStore {
public:
  ~myDataStore();

  void addProduct(Product* p);

  // dynamically allocate the produce when you create it, memory to last beyond create product
  // will be given a pointer to the product
  // not working with user objects and pointing to them in memory
  // creating them with a method.

  void addUser(User* u);

  std::vector<Product*> search(std::vector<std::string>& terms, int type);

  void dump(std::ostream& ofile);

  void addCart(std::string username, Product* p);
  void buyCart(std::string username);
  void viewCart(std::string username);

protected:  
  std::map<std::string, std::vector<Product*>> carts_;
  std::vector<Product*> products_;
  std::map<std::string, User*> users_;
  std::map<std::string, std::set<Product*>> keywords_;
  // std::map<std::string, std::vector<Product*>> userCarts_;
};

#endif