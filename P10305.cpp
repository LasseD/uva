#include <iostream>
#include <vector>
#include <stack>

int main() {
  int n, m, a, b;
  int blockedBy[100];
  std::vector<int> blocks[100];

  while(true) {
    std::cin >> n >> m;
    if(n == 0 && m == 0)
      return 0;
    
    for(int i = 0; i < n; ++i) {
      blockedBy[i] = 0;
      blocks[i].clear();
    }
    for(int i = 0; i < m; ++i) {
      std::cin >> a >> b; // a must complete before b.
      blocks[a-1].push_back(b-1);
      ++blockedBy[b-1];
    }

    std::stack<int> s;
    for(int i = 0; i < n; ++i) {
      if(blockedBy[i] == 0)
	s.push(i);
    }
    bool first = true;
    while(!s.empty()) {
      int t = s.top();
      s.pop();
      if(!first)
	std::cout << " ";
      std::cout << t+1;
      first = false;
      for(std::vector<int>::const_iterator it = blocks[t].begin(); it != blocks[t].end(); ++it) {
	--blockedBy[*it];
	if(blockedBy[*it] == 0)
	  s.push(*it);
      }
    }
    std::cout << std::endl;
  }
}
