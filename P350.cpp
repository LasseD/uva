#include <iostream>

int main() {
  long Z, I, M, L;
  for(int cas = 0; true; ++cas) {
    std::cin >> Z >> I >> M >> L;
    if(Z == 0 && I == 0 && M == 0 && L == 0)
      return 0;
    if(Z < 0 || I < 0 || M < 0 || L < 0) {
      int *die = NULL;
      die[0] = 666;
    }
    // Perform simulation:
    int maxLoopLength = 16;
    bool found = false;
    int loopLength = 0;
    while(!found) {
      maxLoopLength *= 2;
      const long initialSeed = L;
      for(int i = 0; i < maxLoopLength; ++i) {
	L = (Z*L+I) % M;
	if(L == initialSeed) {
	  loopLength = i+1;
	  found = true;
	  break;
	}
      }
    }
    std::cout << "Case " << (cas+1) << ": " << loopLength << std::endl;
  }
}
