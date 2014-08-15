#include <iostream>
#include <stdio.h>
#include <set>
#include <algorithm>
#include <map>

std::string makeAna(const std::string &s) {
  std::string copy(s);
  std::transform(copy.begin(),copy.end(),copy.begin(),::tolower);
  std::sort(copy.begin(), copy.end());
  return copy;
}

int main() {
  std::string word;
  std::set<std::string> duplicateAnas;
  std::map<std::string, std::string> anaToWord;

  while(true) {
    std::cin >> word;
    if(word[0] == '#')
      break;
    std::string ana = makeAna(word);
    if(anaToWord.find(ana) != anaToWord.end()) {
      duplicateAnas.insert(ana);
    }
    else {
      anaToWord.insert(std::make_pair(ana, word));
    }
  }
  std::set<std::string> res;
  for(std::map<std::string, std::string>::const_iterator it = anaToWord.begin(); it != anaToWord.end(); ++it) {
    if(duplicateAnas.find(it->first) == duplicateAnas.end())
      res.insert(it->second);
  }
  for(std::set<std::string>::const_iterator it = res.begin(); it != res.end(); ++it)
    std::cout << *it << std::endl;
  return 0;
}
