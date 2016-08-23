#include <iostream>
#include <stdio.h>
#include <algorithm>

/*
Should have used h = (hours1+hours2)/3
Pay 1: (hours1-h)/h = 3*(hours1-h)/(hours1+hours2) = (3*hours1-(hours1+hours2))/(hours1+hours2) = (2*hours1-hours2)/(hours1+hours2)
 */
int main() {
  int t, hours1, hours2, dollars;
  std::cin >> t;
  for(int cas = 0; cas < t; ++cas) {
    std::cin >> hours1 >> hours2 >> dollars;; // x, y hours, z dollars
    std::cout << dollars*(2*hours1-hours2)/(hours1+hours2) << std::endl;
  }
}
