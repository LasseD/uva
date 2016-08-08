#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>

int main() {
  std::string line;  
  int cases, w;
  std::getline(std::cin, line);
  cases = atoi(line.c_str());
  bool possible[201]; // Possible weights.
  for(int cas = 0; cas < cases; ++cas) {
    memset(possible, false, 201);
    std::getline(std::cin, line);
    std::stringstream ss;
    ss << line;
    int sum = 0;
    while(ss >> w) {
      sum += w;
      for(int j = 201-w; j > 0; --j) {
	if(possible[j])
	  possible[j+w] = true;
      }
      possible[w+1] = true;
    }
    if((sum % 2 == 0) && possible[1+sum/2])
      std::cout << "YES" << std::endl;
    else
      std::cout << "NO" << std::endl;
  }
}
