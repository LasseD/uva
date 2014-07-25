#include <iostream>
#include <stdio.h>

int main() {
  int men[20];
  while(true) {
    int N, k, m;
    std::cin >> N >> k >> m;
    if(N == 0)
      return 0;
    //std::cerr << N << " " <<k << " "<< m << std::endl;
    if(N >= 20)
      throw std::exception();
    // set up:
    int mI = N-1;
    int kI = 0;
    for(int j = 0; j < N; ++j) {
      men[j] = j+1;
    }
    // calculate:
    bool first = true;
    while(N > 0) {
      // Print state:
      /*std::cerr << "{";
      for(int i = 0; i < N; ++i) {
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
      std::cerr << "} size " << N << ", mI=" << mI << " kI=" << kI << std::endl;//*/

      // Kill:
      kI = (kI+(k-1)%N) % N;
      mI = (mI-(m-1)%N+N) % N;
      /*std::cerr << "{";
      for(int i = 0; i < N; ++i) {
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
      std::cerr << "} size " << N << ", mI=" << mI << " kI=" << kI << std::endl;//*/

      if(!first)
	printf(",");
      first = false;
      bool same = kI == mI;
      if(same) {
	printf("%3d", men[kI]);
      }
      else {
	printf("%3d%3d", men[kI], men[mI]);
      }      
      // Move away from dead guys:
      int kII = kI;
      int mII = mI;      
      mI = (mI-1+N)%N;
      if(mI == kII)
	mI = (mI-1+N)%N;
      kI = (kI+1)%N;
      if(kI == mII)
	kI = (kI+1)%N;
      // Shuffle all down:
      for(int j = kII+1; j < N; ++j) {
	men[j-1] = men[j];
      }
      if(mI >= kII)
	mI = (mI-1+N)%N;
      if(kI >= kII)
	kI = (kI-1+N)%N;
      if(mII >= kII)
	mII = (mII-1+N)%N;
      --N;

      if(!same) {
	for(int j = mII+1; j < N; ++j) {
	  men[j-1] = men[j];
	}
	if(mI >= mII)
	  mI = (mI-1+N)%N;
	if(kI >= mII)
	  kI = (kI-1+N)%N;
	--N;
      }
    }
    // output:
    printf("\n");
  }
}
