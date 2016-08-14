#include <iostream>

int main() {
  int T, n, P, Q, a[30];
  std::cin >> T;
  for(int cas = 1; cas <= T; ++cas) {
    std::cin >> n >> P >> Q;
    for(int i = 0; i < n; ++i)
      std::cin >> a[i];
    int sumWeights = 0;
    int eggs = 0;
    int toTry = n < P ? n : P;
    for(int i = 0; i < toTry; ++i) {
      if(sumWeights+a[i] > Q)
	break;
      ++eggs;
      sumWeights += a[i];
    }
    std::cout << "Case " << cas << ": " << eggs << std::endl;
  }
  return 0;
}
