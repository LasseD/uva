#include <iostream>

int main() {
  int t[9];
  while(std::cin >> t[0]) {
    for(int i = 1; i <= 8; ++i)
      std::cin >> t[i];
    bool anyPrinted = false;
    // Print first 8 terms:
    for(int i = 0; i < 8; ++i) {
      if(t[i] == 0)
	continue;
      if(!anyPrinted) {
	if(t[i] < 0) {
	  std::cout << "-";
	  t[i]=-t[i];
	}
      }
      else { // anyPrinted:
	if(t[i] < 0) {
	  std::cout << " - ";
	  t[i] = -t[i];
	}
	else
	  std::cout << " + ";
      }
      anyPrinted = true;
      if(t[i] != 1)
	std::cout << t[i];
      std::cout << "x";
      if(i != 7)
	std::cout << "^" << (8-i);
    }
    // Constant term:
    if(t[8] == 0) {
      if(!anyPrinted)
	std::cout << "0";
    }
    else {
      if(!anyPrinted) {
	std::cout << t[8];
      }
      else {
	if(t[8] < 0)
	  std::cout << " - " << (-t[8]);
	else
	  std::cout << " + " << t[8];	
      }
    }    
    std::cout << std::endl;
  }
}
