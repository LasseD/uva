#include <iostream>

int main() {
  int T, N, C, max;
  std::cin >> T;
  for(int cas = 0; cas < T; ++cas) {
    std::cin >> N;
    max = 0;
    for(int i = 0; i < N; ++i) {
      std::cin >> C;
      if(C > max)
	max = C;
    }
    std::cout << "Case " << (cas+1) << ": " << max << std::endl;
  }
}
