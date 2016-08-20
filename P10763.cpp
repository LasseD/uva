#include <iostream>
#include <limits>
#include <algorithm>

typedef std::pair<int,int> PP;
typedef std::pair<PP,bool> PPB;

int main() {
  int n;
  while(true) {
    std::cin >> n;
    if(n == 0)
      return 0;
    PPB *all = new PPB[n];
    for(int i = 0; i < n; ++i) {
      std::cin >> all[i].first.first >> all[i].first.second;
      if(all[i].first.first > all[i].first.second) {
	std::swap(all[i].first.first, all[i].first.second);
	all[i].second = false;
      }
      else
	all[i].second = true;
    }

    std::sort(all, all+n);
    bool ok = true;
    for(int i = 0; i < n; ++i) {
      int trues = all[i].second ? 1 : -1;
      while(i < n-1 && all[i].first == all[i+1].first) {
	++i;
	trues += all[i].second ? 1 : -1;
      }
      if(trues != 0) {
	std::cout << "NO" << std::endl;
	ok = false;
	break;
      }
    }
    if(ok)
	std::cout << "YES" << std::endl;
    delete[] all;
  }
}
