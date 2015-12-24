#include <iostream>

int main() {
  int t, n, m;
  std::cin >> t;
  for(int i = 0; i < t; ++i) {
    std::cin >> n >> m;
    std::cout << (n/3)*(m/3) << std::endl;
  }
}
