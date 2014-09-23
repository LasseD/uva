#include <iostream>
#include <stdlib.h>

int main() {
  while(true) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    if(x1 == 0)
      return 0;
    if(x1 == x2 && y1 == y2) {
      std::cout << 0 << std::endl;
      continue;
    }
    if(x1 == x2 || y1 == y2) {
      std::cout << 1 << std::endl;
      continue;
    }
    int diffX = abs(x1-x2);
    int diffY = abs(y1-y2);
    if(diffX == diffY) {
      std::cout << 1 << std::endl;
      continue;
    }
    std::cout << 2 << std::endl;
  }
}
