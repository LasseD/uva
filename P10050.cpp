#include <iostream>

int main() {
  bool hartal[3650];
  int T, N, P, H;
  std::cin >> T;
  for(int cas = 0; cas < T; ++cas) {
    std::cin >> N >> P;
    for(int i = 0; i < N; ++i) {
      bool holiday = (i % 7 == 5 || i % 7 == 6);
      hartal[i] = holiday;
    }
    int daysLost = 0;
    for(int i = 0; i < P; ++i) {
      std::cin >> H;
      for(int h = H-1; h < N; h+=H) {
	if(!hartal[h]) {
	  hartal[h] = true;
	  ++daysLost;
	}
      }
    }
    std::cout << daysLost << std::endl;
  }
  return 0;
}
