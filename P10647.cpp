#include <iostream>
#include <stdio.h>

typedef unsigned long long ul;

/*
low a, high b.
Minimize penalty = A*x^2 + (1-x)^2*B for x in [0,1]:
  Ax^2 + (x^2-2x+1)B = (A+B)x^2 - 2Bx + B
  => Minimize at x = 2B/2(A+B) = B/(A+B) (Parabola min of f(x)=ax^2+bx+c is -b/2a)
 */
double minX(int low, int high, long A, long B, double &val) {
  long gap = high-low;
  double x = gap*B/(A+(double)B);
  val = A*x*x + B*(gap-x)*(gap-x);
  //std::cerr << low << "->" << high << ", A=" << A << ", B=" << B << ", x=" << (low+x) << ", f(x)=" << val << std::endl;
  return low + x;
}

int readInt() {
  char c, w[13];
  gets(w);
  int ret = 0;
  for(int i = 0; '0' <= (c = w[i]) && c <= '9'; ++i)
    ret = 10*ret + (c-'0');
  return ret;
}

int main() {
  int n, a[10000];

  while(true) {
    n = readInt();
    if(n == 0)
      return 0;
    // Read input:
    ul high = 0;
    a[0] = readInt();
    for(int i = 1; i < n; ++i) {
      a[i] = readInt();
      ul houseDiff = (a[i]-a[i-1]);
      high += houseDiff*houseDiff*(n-i);
    }

    // Find best house:
    ul low = 0;
    double bestX = a[0];
    double bestHousePrice = high;
    for(int i = 1; i < n; ++i) {
      // Try in space up to next house.
      ul houseDiff = (a[i]-a[i-1]);
      high -= houseDiff*houseDiff*(n-i);
      double midPrice;
      double x = minX(a[i-1], a[i], i, n-i, midPrice);
      double price = low+high+midPrice;
      //std::cerr << "low=" << low << ", high=" << high << ", mid price=" << midPrice << ", TOTAL price=" << price << std::endl;
      if(price < bestHousePrice - 1e-6) {
	bestHousePrice = price;
	bestX = x;
      }
      low += i*houseDiff*houseDiff;
    }
    
    printf("%.3f\n", bestX);
  }
}
