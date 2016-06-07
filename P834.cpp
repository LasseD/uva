#include <iostream>
#include <stdio.h>

int main() {
  long a, b;
  while(std::cin >> a >> b) {
    long b0 = a < 0 ? (a/b-1) : (a/b);
    std::cout << "[" << b0 << ";";

    a -= b0*b;
    
    long x = a/b;
    for(int i = 0; b != 0; ++i) {
      long y = b;
      long z = a%b;
      x = a/b;

      if(i > 1)
	std::cout << ",";
      if(i > 0)
	std::cout << x;

      a = y;
      b = z;
    }

    std::cout << "]" << std::endl;
  }
}
