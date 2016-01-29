#include <iostream>
#include <vector>

typedef std::vector<int> V;

int main() {
  int n;
  while(true) {
    std::cin >> n;
    if(n == 0)
      return 0;
    V v; // top is front.
    for(int i = 1; i <= n; ++i)
      v.push_back(i);
    std::cout << "Discarded cards:";
    bool first = true;
    while(v.size() > 1) {
      if(!first)
	std::cout << ",";
      first = false;
      std::cout << " " << v.front();
      v.erase(v.begin());
      int next = v.front();
      v.erase(v.begin());
      v.push_back(next);      
    }
    std::cout << std::endl << "Remaining card: " << v.front() << std::endl;
  }
}
