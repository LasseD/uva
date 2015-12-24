#include <iostream>

int countBits(int n) {
  int ret = 0;
  while(n > 0) {
    if((n & 1) == 1)
      ++ret;
    n>>=1;
  }
  return ret;
}

int reverse(int n) {
  int ret = 0;
  while(n > 0) {
    ret = 10*ret + (n%10);
    n /= 10;
  }
  return ret;
}

int asHex(int n) {
  n = reverse(n);
  int ret = 0;
  while(n > 0) {
    ret = 16*ret + (n%10);
    n /= 10;
  }
  return ret;
}

int main() {
  int N, M;
  std::cin >> N;
  for(int i = 0; i < N; ++i) {
    std::cin >> M;
    std::cout << countBits(M) << " " << countBits(asHex(M)) << std::endl;
  }
}
