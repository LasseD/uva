#include <iostream>

int main() {
  int N;
  for(int cas = 0; true; ++cas) {
    std::cin >> N;
    if(N < 0)
      return 0;
    int lines = 1;
    int copies = 0;
    while(lines < N) {
      copies++;
      lines *= 2;
    }
    std::cout << "Case " << (cas+1) << ": " << copies << std::endl;
  }
}
