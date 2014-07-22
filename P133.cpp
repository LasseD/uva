#include <iostream>
#include <stdio.h>

int main() {
  int men[20];
  while(true) {
    int N, k, m;
    std::cin >> N >> k >> m;
    if(N == 0)
      return 0;
    // set up:
    int maxI = N;
    int kI = 0;
    int mI = 1;
    for(int j = 0; j < N; ++j) {
      men[(j+1)%N] = N-j;
    }
    // calculate:
    while(maxI > 0) {
      // Print state:
      /*std::cerr << "{";
      for(int i = 0; i < maxI; ++i) {
	std::cerr << " ";
	if(i == kI)
	  std::cerr << "(";
	if(i == mI)
	  std::cerr << "[";
	std::cerr << men[i];
	if(i == mI)
	  std::cerr << "]";
	if(i == kI)
	  std::cerr << ")";
      }
      std::cerr << "} size " << maxI << ", mI=" << mI << " kI=" << kI << std::endl;//*/

      // Kill:
      kI = (kI-(k%maxI-1)+maxI) % maxI;
      mI = (mI+(m%maxI-1)) % maxI;
      /*std::cerr << "{";
      for(int i = 0; i < maxI; ++i) {
	std::cerr << " ";
	if(i == kI)
	  std::cerr << "(";
	if(i == mI)
	  std::cerr << "[";
	std::cerr << men[i];
	if(i == mI)
	  std::cerr << "]";
	if(i == kI)
	  std::cerr << ")";
      }
      std::cerr << "} size " << maxI << ", mI=" << mI << " kI=" << kI << std::endl;//*/

      if(maxI != N)
	printf(",");
      if(kI == mI) {
	printf("%3d", men[kI]);
      }
      else {
	printf("%3d%3d", men[kI], men[mI]);
      }      
      // Remove dead guys:
      // Shuffle all down:
      bool same = kI == mI;
      for(int j = kI; j < maxI-1; ++j) {
	men[j] = men[j+1];
      }
      if(mI > kI)
	mI = (mI-1+maxI)%maxI;
      --maxI;
      if(!same) {
	for(int j = mI; j < maxI-1; ++j) {
	  men[j] = men[j+1];
	}
	if(mI < kI)
	  kI = (kI-1+maxI)%maxI;	
	--maxI;
      }
      if(maxI != 0)
	kI = (kI-1+maxI)%maxI;
    }
    // output:
    printf("\n");
  }
}
