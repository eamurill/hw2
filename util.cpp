#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  set<string> words;
  stringstream ss(rawWords);
  string word;

  

  while(ss >> word){
    word = convToLower(word);
    bool pnct = false;
    for(size_t i = 0; i < word.size(); i++){ 
      if(ispunct(word[i])){
        int punctuation_idx = i;
        pnct = true;
        if(word.substr(0, punctuation_idx).size() >= 2){
          words.insert(word.substr(0, punctuation_idx));
        }
        if(word.substr(punctuation_idx+1).size() >= 2){
          words.insert(word.substr(punctuation_idx+1));
        }
        break;
      }
      
    }

    if(pnct == false && word.size() >= 2){
      words.insert(convToLower(word));
    }
  }
  return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
