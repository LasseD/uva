#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

// http://math.stackexchange.com/questions/396085/how-to-find-area-of-triangle-from-its-medians
int main() {
  double a, b, c;
  while(cin >> a >> b >> c) {
    double s = (a+b+c)/2.0;
    double area = 4.0/3.0*sqrt(s*(s-a)*(s-b)*(s-c));
    if(area > 1e-5)
      printf("%.3lf\n", area);
    else
      printf("-1.000\n");
  }
  return 0;
}
