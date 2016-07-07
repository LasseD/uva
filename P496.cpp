#include <iostream>
#include <stdio.h>
#include <sstream>
#include <set>

typedef std::string String;
typedef std::stringstream SS;
typedef std::set<int> Set;

int main() {
  String line1, line2;
  int e;
  while(std::getline(std::cin,line1) && std::getline(std::cin,line2)) {
    std::stringstream ss1, ss2; 
    ss1 << line1; 
    ss2 << line2;
    Set s1, s2;
    while(ss1 >> e)
      s1.insert(e);
    while(ss2 >> e)
      s2.insert(e);

    unsigned int s1ElementsInS2 = 0;
    unsigned int s2ElementsInS1 = 0;
    for(Set::const_iterator it = s1.begin(); it != s1.end(); ++it) {
      if(s2.find(*it) != s2.end())
	++s1ElementsInS2;
    }
    for(Set::const_iterator it = s2.begin(); it != s2.end(); ++it) {
      if(s1.find(*it) != s1.end())
	++s2ElementsInS1;
    }

    if(s1.empty() || s2.empty()) {
      int *a = NULL; a[2] = 2;
    }

    if(s1ElementsInS2 == s1.size() && s2ElementsInS1 == s2.size())
      std::cout << "A equals B" << std::endl;
    else if(s1ElementsInS2 == s1.size())
      std::cout << "A is a proper subset of B" << std::endl;
    else if(s2ElementsInS1 == s2.size())
      std::cout << "B is a proper subset of A" << std::endl;
    else if(s1ElementsInS2 == 0 && s2ElementsInS1 == 0)
      std::cout << "A and B are disjoint" << std::endl;
    else
      std::cout << "I'm confused!" << std::endl;

  }  
  return 0;
}
