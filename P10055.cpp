#include <iostream>
#include <stdio.h>

int main() {
  while(true) {
    if(!std::cin)
      return 0;
    long long a, b;
    
    std::cin >> a;
    if(!std::cin)
      return 0;
    std::cin >> b;

    if(a < b)
      std::cout << (b-a) << std::endl;
    else
      std::cout << (a-b) << std::endl;      
  }
}
