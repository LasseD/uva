#include <iostream>

int main() {
  int t, n, m; // Readers.
  std::cin >> t;
  for(int ignore = 0; ignore < t; ++ignore) {
    std::cin >> n;
    int min = 9999;
    int max = 0;

    for(int i = 0; i < n; ++i) {
      std::cin >> m;
      if(m < min)
	min = m;
      if(m > max)
	max = m;
    }
    std::cout << ((max-min)*2) << std::endl;
  }
  return 0;
}
