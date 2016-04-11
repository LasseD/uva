#include <iostream>

int main() {
  int N, m;
  for(int cas = 1; true; ++cas) {
    std::cin >> N;
    if(N == 0)
      return 0;
    int sum = 0;
    for(int i = 0; i < N; ++i) {
      std::cin >> m;
      if(m == 0)
	--sum;
      else
	++sum;
    }
    std::cout << "Case " << cas << ": " << sum << std::endl;
  }
}
