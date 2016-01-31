#include <iostream>

int main() {
  int cases, N;
  unsigned long long start0[51], start1[51];
  start0[1] = 1;
  start1[1] = 1;
  for(int i = 2; i <= 50; ++i) {
    start0[i] = start0[i-1]+start1[i-1];
    start1[i] = start0[i-1];
  }

  std::cin >> cases;
  for(int cas = 1; cas <= cases; ++cas) {
    std::cout << "Scenario #" << cas << ":" << std::endl;
    std::cin >> N;    
    std::cout << (start0[N]+start1[N]) << std::endl << std::endl;
  }
}
