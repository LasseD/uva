#include <iostream>

int main() {
  int N, e, f, c;
  std::cin >> N;
  for(int i = 0; i < N; ++i) {
    std::cin >> e >> f >> c;
    int empty = e+f;
    int sum = 0;
    while(empty >= c) {
      int full = empty/c;
      sum += full;
      empty = empty - full*c + full;
    }
    std::cout << sum << std::endl;
  }
}
