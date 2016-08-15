#include <iostream>

int main() {
  long N;
  while(std::cin >> N) {
    int M = 0;
    std::cout << N << " converts to ";
    for(int i = 0; i < 4; ++i) {
      M <<= 8;
      M |= (N & 0xFF);
      N >>= 8;
    }
    std::cout << M << std::endl;
  }
  return 0;
}
