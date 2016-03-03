#include <iostream>
#include <stdio.h>
#include <math.h>

/*
Time 0:
Speed: u
Acceleration: a

Time t:
Speed v
displacement s

s = u*t + 1/2*a*t^2
t = sqrt(2(s - u*t)/a)
 */
int main() {
  int n;
  double u, v, a, s, t;
  for(int cas = 1; true; ++cas) {
    std::cin >> n;
    if(n == 0)
      return 0;
    printf("Case %d: ", cas);
    switch(n) {
    case 1: // u v t:
      std::cin >> u >> v >> t;
      s = (u+v)/2*t;
      a = (v-u)/t;
      printf("%.3f %.3f\n", s, a);
      break;
    case 2:
      std::cin >> u >> v >> a;
      t = (v-u)/a;
      s = (u+v)/2*t;
      printf("%.3f %.3f\n", s, t);
      break;
    case 3:
      std::cin >> u >> a >> s;
      v = sqrt(u*u + 2*a*s);
      t = (v-u)/a;
      printf("%.3f %.3f\n", v, t);
      break;
    case 4:
      std::cin >> v >> a >> s;
      u = sqrt(v*v - 2*a*s);
      t = (v-u)/a;
      printf("%.3f %.3f\n", u, t);
      break;
    }
  }
}
