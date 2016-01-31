#include <iostream>

int main() {
  int j, n, m, c, consumption[20], on[20];
  for(int cas = 1; true; ++cas) {
    std::cin >> n >> m >> c;
    if(n == 0 && m == 0 && c == 0)
      return 0;
    for(int i = 0; i < n; ++i) {
      std::cin >> consumption[i];
      on[i] = false;
    }
    int blown = false;
    int max = 0;
    int curr = 0;
    for(int i = 0; i < m; ++i) {
      std::cin >> j;
      --j;
      if(on[j]) {
	curr -= consumption[j];
      }
      else {
	curr += consumption[j];
	if(curr > max)
	  max = curr;
	if(curr > c)
	  blown = true;	
      }
      on[j] = !on[j];
    }
    std::cout << "Sequence " << cas << std::endl;
    if(!blown) {
      std::cout << "Fuse was not blown." << std::endl;
      std::cout << "Maximal power consumption was " << max << " amperes." << std::endl;
    }
    else {
      std::cout << "Fuse was blown." << std::endl;
    }
    std::cout << std::endl;
  }
}
