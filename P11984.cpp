#include <iostream>
#include <stdio.h>

double CtoF(double c) {
  return 9*c/5+32;
}

// F = 9/5*c+32 => c = (F-32)/9*5
double FtoC(double f) {
  return 5*(f-32)/9;
}

int main() {
  int T; std::cin >> T;
  for(int cas = 1; cas <= T; ++cas) {
    int C, d; std::cin >> C >> d;
    printf("Case %d: %.2f\n", cas, FtoC(d+CtoF(C)));
  }
}
