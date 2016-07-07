#include <iostream>
#include <stdio.h>
#include <cmath>

int main() {
  int cases;
  std::cin >> cases;
  for(int cas = 1; cas <= cases; ++cas) {
    double d, v, u; // d = river width. v = river speed. u = boat speed
    std::cin >> d >> v >> u;
    
    if(v <= 0 || u <= 0 || v >= u) {
      printf("Case %d: can't determine\n", cas);
    }
    else {
      double timeFast = d/u;
      double w = sqrt(u*u-v*v); // speed perpendicular.
      double timeSlow = d/w;
      printf("Case %d: %.3f\n", cas, fabs(timeSlow - timeFast));
    }
  }
}
