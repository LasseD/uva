#include <iostream>
#include <cstring>
#include <cmath>

bool isSquare(int n) {
  int root = (int)(sqrt(n)+0.5);
  //std::cerr << n << ": " << (n == root * root) << std::endl;
  return n == root * root;
}

int main() {
  int T, N, a[50], ret[50];
  for(N = 1; N <= 50; ++N) {
    int pecksInUse = 0;
    for(int i = 1; true; ++i) {
      bool ok = false;
      for(int peck = 0; peck < N; ++peck) {
	if(peck >= pecksInUse || isSquare(a[peck]+i)) {
	  ok = true;
	  a[peck] = i;
	  if(peck >= pecksInUse)
	    ++pecksInUse;
	  break;
	}
      }
      if(!ok) {
	ret[N-1] = i-1;
	break;
      }
    }
  }

  std::cin >> T;
  for(int cas = 0; cas < T; ++cas) {
    std::cin >> N;
    std::cout << ret[N-1] << std::endl;
  }
  return 0;
}
