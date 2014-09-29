#include <iostream>
#include <stdio.h>
#include <map>
#include <sstream>

typedef std::map<std::string,std::string> map;

int main() {
  map dic;
  // Read dictionary:
  char line[23];
  while(true) {
    std::cin.getline(line, 23);
    std::string a, b;
    int part = -1;
    for(int i = 0; i < 23; ++i) {
      if(part == -1) {
	if(line[i] == ' ') {
	  line[i] = '\0';
	  a = std::string(line);
	  part = i+1;
	  continue;
	}
	if(!(line[i] >= 'a' && line[i] <= 'z')) {
	  break;
	}
      }
      else {
	if(!(line[i] >= 'a' && line[i] <= 'z')) {
	  line[i] = '\0';
	  b = std::string(&line[part]);
	  break;
	}
      }
    }
    if(part == -1)
      break;
    dic.insert(std::make_pair(b, a));
    //std::cerr << "Read " << a << " -> " << b << std::endl;
  }
  while(std::cin.getline(line, 12)) {
    for(int i = 0; i < 12; ++i) {
      if(!(line[i] >= 'a' && line[i] <= 'z')) {
	line[i] = '\0';
	break;
      }
    }

    map::const_iterator it = dic.find(std::string(line));
    if(it == dic.end())
      std::cout << "eh" << std::endl;
    else
      std::cout << it->second << std::endl;
  }
}
