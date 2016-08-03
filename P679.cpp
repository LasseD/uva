#include <iostream>
#include <stdio.h>

/*
         1
    2          3
 4    5     6     7
8 9 10 11 12 13 14 15
 */
int main() {
  int D, I, cases;
  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    std::cin >> D >> I;
    --I;
    //int numberOfNodes = (1 << D)-1;
    int nodeI = 1;
    for(int level = 1; level < D; ++level) {
      int even = (I & 1) == 0;
      //std::cerr << "even=" << even << ", I=" << I << ", nodeI=" << nodeI << std::endl;
      I >>= 1;
      nodeI = 2*nodeI + (even ? 0 : 1);
    }
    std::cout << nodeI << std::endl;
  }
  return 0;
}
