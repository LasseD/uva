#include <iostream>

int main() {
  int T, N, A;
  std::cin >> T;
  for(int cas = 1; cas <= T; ++cas) {
    std::cin >> N;
    for(int i = 0; i < N; ++i) {
      std::cin >> A;
      if(N/2 == i)
	std::cout << "Case " << cas << ": " << A << std::endl;
    }
  }
  return 0;
}
