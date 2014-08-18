#include <iostream>

int main() {
  while(true) {
    std::string line;
    std::cin >> line;
    if(line[0] == '#')
      return 0;
    // find tail:
    unsigned int iTail = line.size()-1;
    while(iTail > 0) {
      if(line[iTail-1] < line[iTail])
	break;
      --iTail;
    }
    if(iTail == 0) {
      std::cout << "No Successor" << std::endl;
      continue;
    }
    // find first after last:
    unsigned int replace = line.size()-1;
    while(true) {
      if(line[replace] > line[iTail-1])
	break;
      --replace;
    }
    std::swap(line[iTail-1],line[replace]);
    for(unsigned int i = 0; iTail + i < line.size()-i-1; ++i) {
      std::swap(line[iTail+i],line[line.size()-i-1]);      
    }
    std::cout << line << std::endl;
  }
}
