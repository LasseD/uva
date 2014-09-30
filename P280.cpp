#include <iostream>
#include <vector>
#include <set>
#include <stack>

int main() {
  std::vector<int> neighbours[100];

  while(true) {
    int n;
    std::cin >> n;
    if(n == 0)
      return 0;
    // build graph:
    for(int i = 0; i < n; ++i) {
      neighbours[i].clear();
    }
    while(true) {
      int a;
      std::cin >> a;
      if(a == 0)
	break;
      while(true) {
	int b;
	std::cin >> b;
	if(b == 0)
	  break;
	neighbours[a-1].push_back(b-1);
      }
    }
    // handle queries:
    int numQueries;
    std::cin >> numQueries;
    std::set<int> unreachable;
    for(int ignore = 0; ignore < numQueries; ++ignore) {
      int q;
      std::cin >> q; // query
      --q;
      //std::cerr << (q+1) << " -> ";
      unreachable.clear();
      for(int i = 0; i < n; ++i) {
	unreachable.insert(i);
      }
      std::stack<int> s;
      s.push(q);
      while(!s.empty()) {
	int p = s.top();
	s.pop();
	for(unsigned int i = 0; i < neighbours[p].size(); ++i) {
	  int p2 = neighbours[p][i];
	  if(unreachable.find(p2) != unreachable.end()) {
	    //std::cerr << (p2+1) << " ";
	    unreachable.erase(p2);
	    s.push(p2);
	  }
	}
      }
      //std::cerr << std::endl;
      std::cout << unreachable.size();
      for(std::set<int>::const_iterator it = unreachable.begin(); it != unreachable.end(); ++it) {
	std::cout << " " << (*it + 1);
      }
      std::cout << std::endl;
    }
  }
}
