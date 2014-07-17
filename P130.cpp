#include <iostream>

int main() {
  int men[100];
  while(true) {
    int n, k;
    std::cin >> n >> k;
    if(n == 0)
      return 0;
    // set up:
    int maxI = n-1;
    int i = maxI;
    for(int j = 0; j < n; ++j) {
      men[j] = j+1;
    }
    // calculate:
    while(maxI > 0) {
      // Kill:
      int toDieI = (i + k)%(1+maxI);
      // Walk to replacement:
      int toReplaceI = (toDieI+1)%(1+maxI);
      for(int j = 0; j < k-1; ++j) {
	toReplaceI++;
	if(toReplaceI == toDieI)
	  ++toReplaceI;
	if(toReplaceI == maxI+1)
	  toReplaceI = 0;
      }
      //std::cerr << "Killing " << men[toDieI] << "@" << toDieI << " -> " << men[toReplaceI] << "@" << toReplaceI << std::endl;
      // Replace dead guy:
      men[toDieI] = men[toReplaceI];
      // Shuffle all down:
      for(int j = toReplaceI; j < maxI; ++j) {
	men[j] = men[j+1];
      }
      --maxI;
      // update i:
      i = toDieI;
      if(toDieI > toReplaceI)
	--i;
    }
    // output:
    std::cout << ((n+1-men[0])%n+1) << std::endl;
  }
}
