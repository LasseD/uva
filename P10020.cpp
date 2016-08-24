#include <iostream>
#include <stdio.h>
#include <algorithm>

typedef std::pair<int,int> PP;
#define L first
#define R second

int main() {
  int T, M;
  PP a[100000], b[100000];
  std::cin >> T;
  for(int cas = 0; cas < T; ++cas) {    
    if(cas != 0)
      std::cout << std::endl;
    std::cin >> M;
    int sizeA = 0;
    for(;;++sizeA) {
      std::cin >> a[sizeA].L >> a[sizeA].R;
      if(a[sizeA].L == 0 && a[sizeA].R == 0)
	break;
    } 
    std::sort(a, a+sizeA);

    /*
    std::cerr << "a:";
    for(int i = 0; i < sizeA; ++i)
      std::cerr << " " << a[i].L << "," << a[i].R;
    std::cerr << std::endl;//*/

    int iB = 0; // For output.
    int covered = 0;
    int bestI = -1; // Best of aI / where a[aI].R is max.
    for(int iA = 0; iA < sizeA; ++iA) {
      //std::cerr << "Handling " << iA << ": " << a[iA].L << "," << a[iA].R << ", covered=" << covered << std::endl;
      if(a[iA].L > covered) { // Update b:
	if(bestI == -1 || a[bestI].L > covered)
	  break; // Not OK!
	b[iB++] = a[bestI];
	covered = a[bestI].R;
	if(covered >= M)
	  break; // OK.
	bestI = iA;
      }
      else { // See if a[iA] is better than bestI:
	if(bestI == -1 || a[iA].R > a[bestI].R)
	  bestI = iA;
      }
    }
    if(bestI != -1 && covered < M && a[bestI].L <= covered) {
	b[iB++] = a[bestI];
	covered = a[bestI].R;
    }

    if(covered >= M) {
      std::cout << iB << std::endl;
      for(int i = 0; i < iB; ++i)
	std::cout << b[i].L << " " << b[i].R << std::endl;
    }
    else
      std::cout << 0 << std::endl;
  }
  return 0;
}
