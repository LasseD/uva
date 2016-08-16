#include <iostream>
#include <stdio.h>
#include <math.h>

int gcd(int a, int b) {
  int c;
  while(a != 0) {
     c = a; 
     a = b%a;  
     b = c;
  }
  return b;
}

int main() {
  int N, a[50];
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    for(int i = 0; i < N; ++i)
      std::cin >> a[i];
    int countAll = 0, noCommon = 0;
    for(int i = 0; i < N-1; ++i) {
      for(int j = i+1; j < N; ++j) {
	++countAll;
	int g = gcd(a[i],a[j]);
	if(g == 1)
	  ++noCommon;
      }
    }
    if(noCommon == 0)
      printf("No estimate for this data set.\n");
    else
      printf("%.6f\n", sqrt(countAll*6/((double)noCommon)));
  }
}
