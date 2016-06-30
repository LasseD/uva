#include <iostream>

int main() {
  int N, R;
  for(int cas = 1; true; ++cas) {
    std::cin >> N >> R;
    if(N == 0 && R == 0)
      return 0;
    
    int additional = 0;
    while(N > R && additional <= 26) {
      N-=R;
      ++additional;
    }
    if(additional > 26)
      std::cout << "Case " << cas << ": impossible" << std::endl;
    else
      std::cout << "Case " << cas << ": " << additional << std::endl;
  }
}
