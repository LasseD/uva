#include <iostream>
#include <stdio.h>

int main() {
  int a, b, c;
  while(std::cin >> a >> b >> c) {
    int sum = a+b+c;
    if(sum == 0 || sum == 3)
      std::cout << '*' << std::endl;
    else if(sum == 1)
      std::cout << (a == 1 ? 'A' : b == 1 ? 'B' : 'C') << std::endl;      
    else // sum == 2
      std::cout << (a == 0 ? 'A' : b == 0 ? 'B' : 'C') << std::endl;      
  }
  return 0;
}
