#include <iostream>

int main() {
  unsigned long long N, a[1001];
  a[0] = 1;
  a[1] = 2;
  a[2] = 5;
  a[3] = 13;
  for(int i = 4; i <= 1000; ++i) {
    a[i] = 2*a[i-1] + a[i-2] + a[i-3];
  }

  while(std::cin >> N) {
    std::cout << a[N] << std::endl;
  }
  return 0;
}
