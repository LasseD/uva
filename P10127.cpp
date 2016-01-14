#include <iostream>

typedef unsigned long long ul;

int main() {
  ul n;
  while(std::cin >> n) {
    ul m = n;
    int digits = 0;
    while(m > 0) {
      while(m % 10 == 1) {
	m/=10;
	++digits;
      }
      if(m == 0)
	break;
      m+=n;
    }
    std::cout << digits << std::endl;
  }
  return 0;
}
