#include <iostream>

int main() {
  int n, a, cnts[101];
  while(true) {
    std::cin >> n;
    if(n == 0)
      return 0;
    for(int i = 0; i < 101; ++i)
      cnts[i] = 0;
    for(int i = 0; i < n; ++i) {
      std::cin >> a;
      cnts[a]++;
    }
    bool first = true;
    for(int i = 0; i < 101; ++i) {
      if(cnts[i] == 0)
	continue;
      if(!first)
	std::cout << " ";
      first = false;
      std::cout << i;
      for(int j = 1; j < cnts[i]; ++j)
	std::cout << " " << i;
    }
    std::cout << std::endl;
  }
}
