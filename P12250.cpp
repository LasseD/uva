#include <iostream>
#include <string>
#include <ctype.h>

int main() {
  char w[100];
  int ignore = 0;
  while(true) {
    std::cin.getline(w, 100);
    if(w[0] == '#')
      return 0;
    for(int i = 0; i < 100; ++i) {
      if(!isprint(w[i])) {
	w[i] = '\0';
	break;
      }
    }
    std::string s(w);
    std::cout << "Case " << (++ignore) << ": ";
    if(s == "HELLO")
      std::cout << "ENGLISH";
    else if(s == "HOLA")
      std::cout << "SPANISH";
    else if(s == "HALLO")
      std::cout << "GERMAN";
    else if(s == "BONJOUR")
      std::cout << "FRENCH";
    else if(s == "CIAO")
      std::cout << "ITALIAN";
    else if(s == "ZDRAVSTVUJTE")
      std::cout << "RUSSIAN";
    else
      std::cout << "UNKNOWN";
    std::cout << std::endl;
  }
}
