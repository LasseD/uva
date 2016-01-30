#include <iostream>
#include <stdio.h>
#include <cmath>

double f(int p, int q, int r, int s, int t, int u, double x) {
  return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
}

#define EPS 1e-6

int main() {
  int p, q, r, s, t, u;
  while(std::cin >> p >> q >> r >> s >> t >> u) {
    double fMin = f(p,q,r,s,t,u,0);
    double fMax = f(p,q,r,s,t,u,1);
    if(fMin == 0) {
      printf("%.4f\n", 0.0);
      continue;
    }
    if(fMax == 0) {
      printf("%.4f\n", 1.0);
      continue;
    }
    if((fMin > 0 && fMax > 0) || (fMin < 0 && fMax < 0)) {
      printf("No solution\n");
      continue;
    }

    double xMin = 0;
    double xMax = 1;
    while(true) {
      double x = (xMin+xMax)/2;
      double fx = f(p,q,r,s,t,u,x);
      if(-EPS <= fx && fx <= EPS) {
	printf("%.4f\n", x);
	break;
      }
      if((fMin < 0 && fx < 0) || (fMin > 0 && fx > 0)) {
	xMin = x;
	fMin = fx;
      }
      else {
	xMax = x;
	fMax = fx;
      }
    }
  }
  return 0;
}
