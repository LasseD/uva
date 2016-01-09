#include <iostream>
#include <stdio.h>
#include <algorithm>

void runPermutations(int *perm, int permI, int permSize, int *S, int Si, int SSize) {
  if(permI == permSize) {
    printf("%d", perm[0]);
    for(int j = 1; j < permSize; ++j) {
      printf(" %d", perm[j]);
    }
    printf("\n");
    return;
  }
  // try with Si:
  perm[permI] = S[Si];
  runPermutations(perm, permI+1, permSize, S, Si+1, SSize);
  // Without Si:
  if(SSize - Si > permSize-permI)
    runPermutations(perm, permI, permSize, S, Si+1, SSize);
}

int main() {
  int k;
  int S[13];
  int perm[13];
  bool first = true;
  while(true) {
    std::cin >> k;
    if(k == 0)
      return 0;
    if(!first)
      printf("\n");
    first = false;
    for(int i = 0; i < k; ++i)
      std::cin >> S[i];
    std::sort(S, S+k);
    runPermutations(perm, 0, 6, S, 0, k);
  }
}
