#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>

/*
best = best coloring of black nodes found so far.
black = current coloring.

Heuristic algorithm by Brian Fry. It works for the problem statement, but is not a general solution :-( See earlier revision for my own heuristic (coloring nodes with minimal number of neighbours).
 */
void run(int node, const int n, std::set<int> * const adjacencyList, std::vector<int> &best, std::vector<int> &black) {
  if(node == n) {
    if(best.size() < black.size()) {
      best = black;
    }
    return;
  }

  bool anyBlackNeighbours = false;
  for(std::vector<int>::const_iterator it = black.begin(); it != black.end(); ++it) {
    if(adjacencyList[node].find(*it) != adjacencyList[node].end()) {
      anyBlackNeighbours = true;
      break;
    }      
  }

  if(!anyBlackNeighbours) {
    black.push_back(node);
    run(node+1, n, adjacencyList, best, black);
    black.pop_back();
  } 
  run(node+1, n, adjacencyList, best, black);
}

/*
k = |edges|
n = |nodes|
N = |tests|
 */
int main() {
  std::set<int> adjacencyList[100];  

  int N;
  std::cin >> N;
  for(int ignore = 0; ignore < N; ++ignore) {
    int n, k;
    std::cin >> n >> k;
    for(int i = 0; i < n; ++i)
      adjacencyList[i].clear();
    for(int i = 0; i < k; ++i) {
      int a, b;
      std::cin >> a >> b;
      --a;
      --b;
      adjacencyList[a].insert(b);
      adjacencyList[b].insert(a);
    }

    std::vector<int> best, black;
    run(0, n, adjacencyList, best, black);

    std::cout << best.size() << std::endl;
    for(unsigned int i = 0; i < best.size(); ++i) {
      if(i != 0)
	std::cout << " ";
      std::cout << (best[i]+1);
    }
    std::cout << std::endl;
  }
}
