#include <iostream>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

void die() {
  int *a = NULL; a[2] = 34;
}

int main() {
  int s, a;
  std::string deg;

  while(std::cin >> s >> a >> deg) {
    double dist = s + 6440;
    double angle = a*2.0*M_PI/360.0;
    if(deg[0] == 'm')
      angle /= 60.0;
    if(angle > 2*M_PI)
      die();
    if(angle >= M_PI)
      angle = 2*M_PI-angle;

    double arc = dist * angle;
    // sin a/2 = chord/2 / dist
    double chord = sin(angle/2) * dist * 2;
    printf("%.6f %.6f\n", arc, chord);
  }
}
