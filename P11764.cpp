#include <iostream>

int main() {
  int T, N, last, curr;
  std::cin >> T;
  for(int cas = 0; cas < T; ++cas) {
    std::cin >> N >> last;
    int up = 0;
    int down = 0;
    for(int i = 1; i < N; ++i) {
      std::cin >> curr;
      if(curr > last)
	++up;
      else if(curr < last)
	++down;
      last = curr;
    }
    std::cout << "Case " << (cas+1) << ": " << up << " " << down << std::endl;
  }
}
