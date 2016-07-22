#include <iostream>
#include <stdio.h>

int main() {
  int N, a;
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    bool first = true;
    for(int i = 0; i < N; ++i) {
      std::cin >> a;
      if(a == 0)
	continue;
      if(!first)
	std::cout << " ";
      std::cout << a;
      first = false;
    }
    if(first)
      std::cout << "0" << std::endl;      
    else
      std::cout << std::endl;
  }
}
