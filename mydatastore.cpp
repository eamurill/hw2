#include <string>
#include <set>
#include <vector>
#include <queue>
#include <sstream>
#include <iomanip>
#include <map>
#include <iostream>

#include "product.h"
#include "user.h"
#include "mydatastore.h"
#include "util.h"


myDataStore::~myDataStore() {
   
  // if(products_.size() < 1){
  //   return;
  // }
  for(size_t i = 0; i < products_.size(); i++) {
    delete products_[i];
  }

  std::map<std::string, User*>::iterator itUser;
  for(itUser = users_.begin(); itUser != users_.end(); ++itUser) {
    delete itUser->second;
  }
}

void myDataStore::addProduct(Product* p) {
    // if (p != nullptr) {
    //     products_.push_back(p);  // Store product pointer
    //     // Index keywords for search functionality
    // }
    if (p != nullptr) {
      products_.push_back(p);  // Store product pointer

      // Get the set of keywords from the product
      std::set<std::string>::iterator itProd;
      for(std::string keyword: p->keywords()){
        if(keywords_.find(keyword) != keywords_.end()){
          keywords_[convToLower(keyword)].insert(p);
        }
        else {
          std::set<Product*> keySet;
          keySet.insert(p);
          keywords_.insert(std::pair<std::string, std::set<Product*>>(keyword, keySet));
        }
      }
    }
}

void myDataStore::addCart(std::string username, Product* p) {
  username = convToLower(username); // case insensitive 

  // Find the user in the users_ map
  std::map<std::string, User*>::iterator it = users_.find(username);
  if (it == users_.end()) {
    // Invalid user
    std::cout << "Invalid request" << std::endl; 
    return;
  }

  // Check if the user already has a cart
  std::map<std::string, std::vector<Product*>>::iterator cart_it = carts_.find(username);
  if (cart_it == carts_.end()) {
    // Create a new empty cart for the user
    std::vector<Product*> newProd;
    carts_.insert(std::make_pair(username, newProd));
  }

  // Add the product to the user's cart
  carts_[username].push_back(p);
  
}

// This function is done

// you want to create protected data members

void myDataStore::buyCart(std::string username){
  
  if(users_.find(username) == users_.end()){
    std::cout << "Invalid username" << std::endl;
    return;
  }
  else {
    for(size_t i = 0; i < carts_[username].size(); ++i){
      if((carts_[username][i]->getQty() > 0) && (users_[username]->getBalance() >=  carts_[username][i]->getPrice())){ // check if 
        double productPrice =  carts_[username][i]->getPrice();
        double userBalance = users_[username]->getBalance();
        carts_[username][i]->subtractQty(1);
        users_[username]->deductAmount(productPrice);
        carts_[username].erase(i+carts_[username].begin());
        i--;
      }
      else{
        std::cout << "You do not have enough money" << std::endl;
      }
    }
  }
}


void myDataStore::viewCart(std::string username){
  // case insensitive 

  // Print invalid if the username doesn't exist 
  
  if(users_.find(username) == users_.end()){
    // Invalid 
    std::cout << "Invalid username" << std::endl; 
    return; // Do not process the quest 
  }

  if(carts_.empty()){ // Cart is empty 
    std::cout << "Cart is empty" << std::endl; 
  }
  
  // But we only want to iterate on this username 
  // User* user = it->second;
  // std::vector<Product*> userCart = carts_[username];

  // int itemCnt = 1;
  
  // // Loop through the vector to print out each product's display  
  // for(Product* product : userCart){
  //   std::cout << "Item " << itemCnt << std::endl;
  //   std::cout << userCart->displayString() << std::endl;
  //   itemCnt++;
  std::vector<Product*> userCart = carts_[username];

  int itemCnt = 1;
  
  // Loop through the vector to print out each product's display  
  for(size_t i=0; i < userCart.size(); i++){
    std::cout << "Item " << itemCnt << std::endl;
    std::cout << userCart[i]->displayString() << std::endl;
    itemCnt++;
  }
}

  
void myDataStore::addUser(User* u) {
   if (u != nullptr) {
        users_.insert(std::pair<std::string, User*> (u->getName(), u));  // Store user pointer
    }
}

// look at inputs and outputs for test cases, look at inputs and outputs for two users, try to identify patterns of what is wrong
std::vector<Product*> myDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> resultSet;
    std::vector<std::string>::iterator termIt;
    

    for(termIt = terms.begin(); termIt != terms.end(); ++termIt) { // Right here I'm going through my terms
      std::map<std::string, std::set<Product*>>::iterator it = keywords_.find(convToLower(*termIt)); //
      // for size_t i = 0; i < keywords_.size(); i++) Keywords[i]
      if(it != keywords_.end()){
        if(resultSet.empty() == true) {
            resultSet = it->second;  // Initialize with first keyword match
        }
        else {
          if(type == 0) {  // AND search (intersection)
            resultSet = setIntersection(resultSet, it->second);

          } 
          else{  // OR search (union)
            resultSet = setUnion(resultSet, it->second);
          }
        }
      }
    }
      // do I need to push back into Products, but I want to call my key function
    std::vector<Product*> ret_val(resultSet.begin(), resultSet.end());
    return ret_val;

}

void myDataStore::dump(std::ostream& ofile) {
  // make sure it's in the 
  // Products, User
  ofile << "<products>\n";
  for(std::vector<Product*>::iterator itProduct = products_.begin(); itProduct != products_.end(); ++itProduct) {
    (*itProduct)->dump(ofile); 
  }
  ofile << "</products>\n";
  

  ofile << "<users>\n";
  for (std::map<std::string, User*>::iterator itUser = users_.begin(); itUser != users_.end(); ++itUser) {
    itUser->second->dump(ofile);  
  }
  ofile << "</users>\n";

}
