#include <iostream>
#include <vector>
#include <stdio.h>

int main() {
  char line[1000];
  while(true) {
    std::cin.getline(line, 100);
    std::vector<int> v;
    int size = 0;
    for(; true; ++size) {
      char c = line[size];
      if(!isprint(c))
	break;
      if(c >= 'a' && c <= 'z')
	v.push_back(c-'a');
      else if(c >= 'A' && c <= 'Z')
	v.push_back(c-'A');      
    }
    if(size == 4) {
      line[4] = '\0';
      if(std::string(line) == "DONE")
	return 0;
    }
    bool ok = true;
    if(v.size() > 1) {
      for(unsigned int i = 0, j = v.size()-1; i < j; ++i, --j) {
	if(v[i] != v[j]) {
	  ok = false;
	  break;
	}
      }
    }
    if(ok)
      std::cout << "You won't be eaten!" << std::endl;
    else 
      std::cout << "Uh oh.." << std::endl;
  }
}
