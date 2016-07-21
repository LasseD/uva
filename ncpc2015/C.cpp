#include <iostream>
#include <ctype.h>

int main() {
  char w[400];
  std::cin.getline(w, 400);
  int ret = 0;
  for(int i = 0; isprint(w[i]); ++i) {
    char c = w[i];
    if(i % 3 == 0) {
      if(c != 'P') 
	++ret;
    }
    else if(i % 3 == 1) {
      if(c != 'E')
	++ret;
    }
    else {
      if(c != 'R')
	++ret;
    }
  }
  std::cout << ret << std::endl;
}
