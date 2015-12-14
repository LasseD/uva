#include <iostream>
#include <stdio.h>

int main() {
  int G[400]; // Graph G[i*20+j] = distance i->j.

  // Continue until EOF:
  for(int testSet = 1; true; ++testSet) {
    // Reset graph:
    for(int i = 0; i < 400; ++i)
      G[i] = 100;

    // Read 19 country lines:
    for(int i = 0; i < 19; ++i) {
      int I, J;
      if(!(std::cin >> I))
	return 0; // Done.
      for(int j = 0; j < I; ++j) {
	std::cin >> J; // J in 1..20
	--J; // 0..19.
	G[20*i + J] = G[20*J + i] = 1; 
      }
    }

    // Graph relaxation:
    bool improved = true;
    while(improved) {
      improved = false;
      for(int i = 0; i < 19; ++i) {
	for(int j = i+1; j < 20; ++j) {
	  // Investigate i->j. See if it can be improved by i->k->j:
	  for(int k = 0; k < 20; ++k) {
	    if(k == i || k == j)
	      continue;
	    if(G[20*i+k] + G[20*k+j] < G[20*i+j]) {
	      improved = true;
	      G[20*i+j] = G[20*j+i] = G[20*i+k] + G[20*k+j];
	    }
	  }
	}
      }
    }

    int pairs, A, B;
    std::cin >> pairs;
    printf("Test Set #%d\n", testSet);
    for(int i = 0; i < pairs; ++i) {
      std::cin >> A >> B;
      printf("%2d to %2d: %d\n", A, B, G[20*(A-1)+(B-1)]);      
    }
    printf("\n");
  }
}
