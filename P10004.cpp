#include <iostream>
#include <vector>
#include <stack>

int main() {
  int colors[200]; // 0 = uncolored, 1 = red, 2 = black.
  bool handled[200];
  std::vector<int> adjacencyList[200];

  while(true) {
    int n, l;
    std::cin >> n;
    if(n == 0)
      return 0;
    for(int i = 0; i < n; ++i) {
      colors[i] = 0;
      handled[i] = false;
      adjacencyList[i].clear();
    }
    colors[0] = 1;
    std::cin >> l;
    //std::cerr << "n: " << n << ", l:" << l << std::endl;
    for(int i = 0; i < l; ++i) {
      int a, b;
      std::cin >> a >> b;
      adjacencyList[a].push_back(b);
      adjacencyList[b].push_back(a);
    }
    std::stack<int> s;
    s.push(0);
    bool notBicolorable = false;
    while(!s.empty() && !notBicolorable) {
      int t = s.top();
      s.pop();
      if(handled[t])
	continue; // Already handled
      for(std::vector<int>::iterator it = adjacencyList[t].begin(); it != adjacencyList[t].end(); ++it) {
	int neighbour = *it;
	if(colors[neighbour] == 0) {
	  colors[neighbour] = 3-colors[t];
	  s.push(neighbour);
	}
	else if(colors[neighbour] == colors[t]) {
	  std::cout << "NOT BICOLORABLE." << std::endl;
	  notBicolorable = true;
	  break;
	}
      } // for iterator
      handled[t] = true;
    } // while(!s.empty() && !done)
    if(!notBicolorable)
      std::cout << "BICOLORABLE." << std::endl;
  } // while(true)
}
