#include <iostream>
#include <stdio.h>

typedef unsigned long long ul;

int main() {
  ul n, m;
  while(std::cin >> n >> m) {
    ul n2 = n;
    bool boring = n < 2 || m < 2 || m > n;
    while(!boring && n2 > 1) {
      if(n2 % m != 0)
	boring = true;
      n2/=m;
    }
    if(n2 != 1)
      boring = true;
    if(boring)
      std::cout << "Boring!" << std::endl;
    else {
      while(n > 1) {
	std::cout << n << " ";
	n/=m;
      }
      std::cout << 1 << std::endl;      
    }
  }
  return 0;
}
