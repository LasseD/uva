#include <iostream>

int main() {
  int T, N, K, P;
  std::cin >> T;
  for(int cas = 0; cas < T; ++cas) {
    std::cin >> N >> K >> P;
    std::cout << "Case " << (cas+1) << ": " << (((K-1+P)%N)+1) << std::endl;
  }
}
