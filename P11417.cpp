#include <iostream>
#include <stdio.h>

typedef unsigned long long ul;

ul gcd(ul a, ul b) {
  ul c;
  while(a != 0) {
     c = a; 
     a = b%a;  
     b = c;
  }
  return b;
}

/*
G_N = G_{N-1} + SUM_{i=N-1,j=i+1<N}GCD(i,j)
 */
int main() {
  ul a[500]; // For N = index+2
  a[0] = gcd(1,2); // N=2: i=1, j=2
  for(int i = 1; i < 500; ++i) {
    int N = i+2;
    // sum1 is the sum for i = N-1:
    a[i] = a[i-1];
    for(int j = 1; j < N; ++j)
      a[i] += gcd(j, N);
  }

  int N;
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    std::cout << a[N-2] << std::endl;
  }
}
