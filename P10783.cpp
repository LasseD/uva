#include <iostream>

int main() {
  int T, a, b;
  std::cin >> T;
  for(int ig = 0; ig < T; ++ig) {
    std::cin >> a >> b;
    if(a == b) {
      if(a % 2 == 0) {
	std::cout << "Case " << (ig+1) << ": " << 0 << std::endl;
	continue;
      }
      else {
	std::cout << "Case " << (ig+1) << ": " << a << std::endl;
	continue;
      }
    }
    int sum = 0;
    for(int i = a; i <= b; ++i) {
      if(i % 2 == 1)
	sum += i;
    }
    std::cout << "Case " << (ig+1) << ": " << sum << std::endl;
  }
  return 0;
}
