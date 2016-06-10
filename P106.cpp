#include <iostream>
#include <stdio.h>

#define MAX 1000000

int gcd(int a, int b) {
  int c;
  while(a != 0) {
     c = a; 
     a = b%a;  
     b = c;
  }
  return b;
}


/*
Given 0 < N <= 1.000.000

Output
A = number of relatvely prime tripples with components <= N.
B = number of integers not part of any tripple <= N

Any number in B: Can't be k times (m^2-n^2), 2nm, or m^2+n^2.

Eample: N = 10:
1 4 9 16 25 36 49 64 81 100
 Relatively prime tripples: (3, 4, 5)
 Other tripples: (6, 8, 10)
 Numbers not in components: 1, 2, 7, 9
 */
int main() {
  int N;
  while(std::cin >> N) {
    bool *notHit = new bool[N+1];
    for(int i = 0; i < N+1; ++i)
      notHit[i] = true;
    
    int A = 0;
    int B = N;

    for(int m = 2; m*m < N; ++m) {
      for(int n = (m%2 == 0) ? 1 : 2; n < m; n+=2) {
	if(gcd(n, m) != 1)
	  continue;
	if(n*n+m*m > N)
	  break;
	// Primitime: (m^2-n^2), 2nm, or m^2+n^2.
	int a = m*m-n*n;
	int b = 2*n*m;
	int c = m*m+n*n;
	++A;
	for(int k = 1; k*c <= N; ++k) {
	  if(notHit[a*k]) {
	    notHit[a*k] = false;
	    --B;
	  }
	  if(notHit[b*k]) {
	    notHit[b*k] = false;
	    --B;
	  }
	  if(notHit[c*k]) {
	    notHit[c*k] = false;
	    --B;
	  }
	}
      } 
    }
    delete[] notHit;
    std::cout << A << " " << B << std::endl;
  }
  return 0;
}
