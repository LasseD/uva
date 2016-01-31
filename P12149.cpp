#include <iostream>

int main() {
  int N;
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    unsigned long sum = 0;
    for(int size = 1; size <= N; ++size) {
      sum += (N-size+1)*(N-size+1);
    }
    std::cout << sum << std::endl;
  }
}
