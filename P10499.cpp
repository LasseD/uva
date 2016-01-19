#include <iostream>
#include <stdio.h>

// Area of circle: PI*r^2
// Surface area of sphere: 4*PI*r^2
int main() {
  long N;
  while(true) {
    std::cin >> N;
    if(N < 0)
      return 0;
    long profit = (N == 1) ? 0 : N;
    printf("%li%%\n", 25*profit);
  }
}
