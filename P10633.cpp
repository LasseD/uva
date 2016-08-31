#include <iostream>
#include <stdio.h>
#include <set>

int main() {
  long long nm;
  while(true) {
    std::cin >> nm;
    if(nm == 0)
      return 0;
    std::set<long long> s;
    for(int c = 9; c >= 0; --c) {
      long long m = (nm-c)/9;
      if(nm != 9*m+c)
	continue;
      s.insert(10*m+c);
    }
    bool first = true;
    for(std::set<long long>::const_iterator it = s.begin(); it != s.end(); ++it) {
      if(!first)
	std::cout << " ";
      first = false;
      std::cout << *it;
    }
    std::cout << std::endl;
  }
}
