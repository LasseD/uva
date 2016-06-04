#include <iostream>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

// https://en.wikipedia.org/wiki/Inradius
int main() {
  double a, b, c;
  while(std::cin >> a >> b >> c) {
    double s = (a+b+c)/2; // Semiperimeter
    double rr = (s-a)*(s-b)*(s-c)/s;
    printf("The radius of the round table is: %.3f\n", s <= 1e-6 ? 0 : sqrt(rr));
  }
}
