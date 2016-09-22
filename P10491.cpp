#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
  int cow, car, show;
  while(cin >> cow >> car >> show) {
    int all = cow+car;
    double pCar = car/(double)(cow+car);
    printf("%.5lf\n", (pCar*(car-1)+(1-pCar)*car)/(all-show-1.0));
  }
  return 0;
}
