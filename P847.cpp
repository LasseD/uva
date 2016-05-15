#include <iostream>

typedef unsigned long long ul;

int main() {
  ul n, p;
  while(std::cin >> n) {
    bool stan = true;
    p = 1;
    while(p < n) {
      if(stan)
	p*=9;
      else
	p*=2;
      stan = !stan;
    }
    if(!stan)
      std::cout << "Stan wins." << std::endl;
    else
      std::cout << "Ollie wins." << std::endl;
  }
  return 0;
}
