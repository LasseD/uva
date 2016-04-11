#include <iostream>

#define MAX_INT 99999999
#define MAX(a,b) ((a < b) ? (b) : (a))

/*
Crossings 1 .. C
S streets, Q queries.
 */
int main() {
  int C, S, Q, c1, c2, d, M[10000];
  for(int cas = 1; true; ++cas) {
    std::cin >> C >> S >> Q;
    if(C == 0 && S == 0 && Q == 0)
      return 0;
    if(cas != 1)
      std::cout << std::endl;
    std::cout << "Case #" << cas << std::endl;
    for(int i = 0; i < C*C; ++i) {
      M[i] = MAX_INT;
    }
    for(int i = 0; i < S; ++i) {
      std::cin >> c1 >> c2 >> d;
      --c1;--c2;
      M[c1*C+c2] = M[c2*C+c1] = d;
    }
    
    // Compute graph:
    bool anyImprovements = true;
    while(anyImprovements) {
      anyImprovements = false;
      // Iterate matrix:
      for(int i = 0; i < C; ++i) {
	for(int j = i+1; j < C; ++j) {
	  for(int k = 0; k < C; ++k) {
	    if(k == i || k == j)
	      continue;
	    if(M[i*C+j] > MAX(M[i*C+k],M[k*C+j])) {
	      anyImprovements = true;
	      M[i*C+j] = M[j*C+i] = MAX(M[i*C+k],M[k*C+j]);
	    }
	  } // for k
	} // for j
      } // for i
    } // while anyImprovements

    // Handle queries:
    for(int i = 0; i < Q; ++i) {
      std::cin >> c1 >> c2;
      --c1;--c2;
      if(M[c1*C+c2] == MAX_INT)
	std::cout << "no path" << std::endl;
      else
	std::cout << M[c1*C+c2] << std::endl;
    }
  }
}
