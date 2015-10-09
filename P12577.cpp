#include <iostream>
#include <string>
#include <ctype.h>

int main() {
  char w[100];
  int ignore = 0;
  while(true) {
    std::cin.getline(w, 100);
    if(w[0] == '*')
      return 0;
    for(int i = 0; i < 100; ++i) {
      if(!isprint(w[i])) {
	w[i] = '\0';
	break;
      }
    }
    std::string s(w);
    std::cout << "Case " << (++ignore) << ": ";
    if(s == "Hajj")
      std::cout << "Hajj-e-Akbar";
    else
      std::cout << "Hajj-e-Asghar";
    std::cout << std::endl;
  }
}
