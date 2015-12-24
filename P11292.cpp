#include <iostream>
#include <algorithm>

int main() {
  int n, m;
  unsigned long heads[20000], knights[20000];
  while(true) {
    std::cin >> n >> m;
    if(n == 0 && m == 0)
      return 0;
    for(int i = 0; i < n; ++i)
      std::cin >> heads[i];
    std::sort(heads, heads+n);
    for(int i = 0; i < m; ++i)
      std::cin >> knights[i];
    std::sort(knights, knights+m);
    int i = 0;
    int j = 0;
    unsigned long cost = 0;
    while(true) {
      if(i == n) {
	std::cout << cost << std::endl;
	break;
      }
      if(j == m) {
	std::cout << "Loowater is doomed!" << std::endl;
	break;
      }
      if(knights[j] < heads[i]) {
	++j;
      }
      else {
	cost += knights[j];
	++i;
	++j;
      }	
    }
  }
}
