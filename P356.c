#include "stdio.h"

int main() {
  int inside[151], outside[151];
  int n, x, y, X, Y, first, i, o, N;

  for(n = 1; n <= 150; ++n) {
    i = 0, o = 0;

    N = 2*n-1;
    for(x = 0; x < n; ++x) {
      for(y = 0; y < n; ++y) {
	X = 2*x;
	Y = 2*y;
	if((X+2)*(X+2)+(Y+2)*(Y+2) <= N*N)
	  ++i;
	if(X*X+Y*Y >= N*N)
	  ++o;	
      }
    }

    //cerr << "n=" << n << " => inside " << i << ", outside: " << o << endl;
    inside[n] = i*4;
    outside[n] = n*n*4 - o*4 - i*4;
  }

  first = 1;
  while(scanf("%d", &n) == 1) {
    // Output:
    if(!first)
      printf("\n");
    first = 0;

    printf("In the case n = %d, %d cells contain segments of the circle.\n", n, outside[n]);
    printf("There are %d cells completely contained in the circle.\n", inside[n]);
  }
  return 0;
}
