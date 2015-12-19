#include <iostream>

int main() {
  unsigned long n, f, x, y, z;
  std::cin >> n;
  for(unsigned long ignore = 0; ignore < n; ++ignore) {
    std::cin >> f;
    unsigned long sum = 0;
    for(unsigned long i = 0; i < f; ++i) {
      std::cin >> x >> y >> z;
      sum += x * z;
    }
    std::cout << sum << std::endl;
  }
}
