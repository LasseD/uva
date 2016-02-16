#include <iostream>

#define MIN(a,b) (((a) < (b)) ? (a) : (b))

int main() {
  int N, code[1009], codeCounts[9], a, aCounts[9];
  for(int cas = 1; true; ++cas) {
    std::cin >> N;
    if(N == 0)
      return 0;
    std::cout << "Game " << cas << ":" << std::endl;
    for(int i = 0; i < 9; ++i)
      codeCounts[i] = 0;
    for(int i = 0; i < N; ++i) {
      std::cin >> code[i];
      --code[i];
      ++codeCounts[code[i]];
    }

    while(true) {
      bool allZero = true;
      int strong = 0;
      for(int i = 0; i < 9; ++i)
	aCounts[i] = 0;

      for(int i = 0; i < N; ++i) {
	std::cin >> a;
	if(a == 0)
	  continue;
	allZero = false;
	--a;

	if(code[i] == a)
	  ++strong;
	++aCounts[a];
      }
      if(allZero)
	break;
      // Count all:
      int all = 0;
      for(int i = 0; i < 9; ++i)
	all += MIN(aCounts[i],codeCounts[i]);
      //std::cerr << "all: " << all << std::endl;
      std::cout << "    (" << strong << "," << (all-strong) << ")" << std::endl;
    }
  }
}
