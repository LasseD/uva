#include <iostream>

typedef unsigned long long ul;

struct MatrixInfo {
  int N, M;
  ul multiplications;
};

ul findOptimalMultiplication(MatrixInfo const * const a, int minI, int maxI, bool print) {
  if(minI == maxI) {
    if(print)
      std::cout << "A" << (minI+1);
    return 0;
  } 
  ul best = -1;
  int bestSizeLeft = 0;
  for(int sizeLeft = 1; sizeLeft+minI <= maxI; ++sizeLeft) {
    ul cur = 
      findOptimalMultiplication(a, minI, minI+sizeLeft-1, false) +
      findOptimalMultiplication(a, minI+sizeLeft, maxI, false) + 
      a[minI].N * a[minI+sizeLeft].N * a[maxI].M;
    if(cur < best) {
      best = cur;
      bestSizeLeft = sizeLeft;
    }
  }
  if(print) {
    std::cout << "(";
    findOptimalMultiplication(a, minI, minI+bestSizeLeft-1, true);
    std::cout << " x ";
    findOptimalMultiplication(a, minI+bestSizeLeft, maxI, true);
    std::cout << ")";
  }
  //std::cerr << "Best for " << minI << "->" << maxI << ": " << best << std::endl;
  return best;
}

int main() {
  MatrixInfo a[10];
  int N;
  
  for(int cas = 1; true; ++cas) {
    std::cin >> N;
    if(N == 0)
      return 0;
    for(int i = 0; i < N; ++i)
      std::cin >> a[i].N >> a[i].M;
    std::cout << "Case " << cas << ": ";
    findOptimalMultiplication(a, 0, N-1, true);
    std::cout << std::endl;
  } 
}
