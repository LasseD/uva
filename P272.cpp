#include <iostream>
#include <stdio.h>

#define LINE_LENGTH 10000

int main() {
  bool first = true;
  char c, line[LINE_LENGTH];
  while(std::cin.getline(line, LINE_LENGTH)) {
    for(int i = 0; isprint(c = line[i]); ++i) {
      if(c == '"') {
	if(first)
	  std::cout << "``";	  
	else
	  std::cout << "''";//"´´"; 
	first = !first;
      }
      else
	std::cout << c;
    }
    std::cout << std::endl;
  }
  return 0;
}
