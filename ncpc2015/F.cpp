#include <iostream>

int main() {
  bool canBe[10001];
  bool canNew[10001];

  int f, ti, ni, ta, tb;
  std::cin >> f;
  for(int i = 0; i < f; ++i) {
    std::cin >> ti >> ni;

    for(int p = 0; p <= ti; ++p) {
      canBe[p] = true;
    }

    for(int j = 0; j < ni; ++j) {
      std::cin >> ta >> tb;
      int diff = tb - ta;
      
      for(int p = 0; p <= ti; ++p) {
	canNew[p] = false;
      }

      bool canSolve = false;
      for(int k = 0; k <= ti; ++k) {
	if(canBe[k]) {
	  if(k >= diff) {
	    canNew[k-diff] = true;
	    canSolve = true;
	  }
	  if(k+diff <= ti) {
	    canNew[k+diff] = true;
	    canSolve = true;
	  }
	}	
      }

      if(!canSolve) {
	std::cout << "impossible" << std::endl;
	return 0;
      }
      for(int p = 0; p <= ti; ++p) {
	canBe[p] = canNew[p];
      }

    } // for ni

  } // for f
  std::cout << "possible" << std::endl;
  return 0;
}
