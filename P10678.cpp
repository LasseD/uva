#include <iostream>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

int main() {
  int T, D, L;
  cin >> T;
  for(int cas = 0; cas < T; ++cas) {
    cin >> D >> L;
    printf("%.3lf\n", M_PI*L/4.0*sqrt(L*L-D*D));
  }
  return 0;
}
