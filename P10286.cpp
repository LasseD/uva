#include <iostream>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

typedef long double ld;

int main() {
  ld F;
  ld a = 108*M_PI/180;
  ld mult = sin(a) / sin(M_PI-a-(a/2.0 - M_PI/4));
  while(std::cin >> F) {
    printf("%.10LF\n", mult*F);
  };
  return 0;
}
