#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stack>

typedef std::pair<int,int> PP;

int main() {
  int *citizens = new int[30000]; // citizen -> edge index.
  PP *edges = new PP[1000000];

  int cases, N, M, a, b;
  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    // Read and setup data:
    std::cin >> N >> M;
    for(int i = 0; i < N; ++i)
      citizens[i] = -1;
    for(int i = 0; i < M; ++i) {
      std::cin >> a >> b;
      --a;
      --b;
      edges[2*i].first = a;
      edges[2*i].second = b;
      edges[2*i+1].first = b;
      edges[2*i+1].second = a;
    }
    std::sort(edges, edges+2*M);
    int prev = -1;
    for(int i = 0; i < 2*M; ++i) {
      if(edges[i].first != prev) {
	prev = edges[i].first;
	citizens[prev] = i;
      }
    }
    
    // Compute connected components:
    int max = 1; // 1 if no one has any friends.
    std::stack<int> s;
    for(int i = 0; i < N; ++i) {
      if(citizens[i] == -1)
	continue; // Already handled.
      int size = 0;
      s.push(i);
      while(!s.empty()) {
	int citizen = s.top();
	s.pop();
	if(citizens[citizen] == -1)
	  continue; // Already handled.
	++size;
	for(int j = citizens[citizen]; edges[j].first == citizen; ++j) {
	  s.push(edges[j].second);
	}
	citizens[citizen] = -1;
      } // while(!s.empty)
      if(size > max)
	max = size;
    } // for i
    std::cout << max << std::endl;
  } // for case

  delete[] edges;
  delete[] citizens;
  return 0;
}
