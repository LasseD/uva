#include <iostream>

typedef unsigned long long ul;

int main() {
  long long n;
  while(std::cin >> n) {
    bool done = false;
    if(n < 0) {
      n = -n;
      if(n%2 == 0)
	std::cout << "Underflow!" << std::endl;
      else
	std::cout << "Overflow!" << std::endl;
      continue;
    }

    ul fac = 1;    
    for(long long i = 1; i <= n; ++i) {
      fac *= i;
      if(fac > 6227020800) {
	std::cout << "Overflow!" << std::endl;
	done = true;
	break;
      }	
    }
    if(!done) {
      if(fac < 10000)
	std::cout << "Underflow!" << std::endl;
      else
	std::cout << fac << std::endl;
    }
  }
  return 0;
}
