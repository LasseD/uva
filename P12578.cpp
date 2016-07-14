#include <iostream>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>

int main() {
  int T, L;
  std::cin >> T;
  for(int ii = 0; ii < T; ++ii) {
    std::cin >> L;
    double allArea = L*L*6.0/10.0;
    double r = L*2.0/10.0;
    double redArea = M_PI*r*r;
    printf("%.2f %.2f\n", redArea, allArea-redArea);
  }
}
