#include <iostream>
#include <stdio.h>
#include <set>
#include <queue>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
typedef std::set<int> Neighbours;

int BFS(int s, int t, int n, Neighbours *edges, int *prev, int *capacityMatrix, int *flowMatrix) {
  for(int i = 0; i < n; ++i)
    prev[i] = -1;
  prev[s] = -2;

  int pathCapacity[100];
  pathCapacity[s] = 2147483647;

  std::queue<int> q;
  q.push(s);
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    for(Neighbours::const_iterator it = edges[u].begin(); it != edges[u].end(); ++it) {
      int v = *it;
      int uvIdx = u*n+v;
      int residualCapacity = capacityMatrix[uvIdx] - flowMatrix[uvIdx];
      if(residualCapacity <= 0 || prev[v] != -1)
	continue;
      prev[v] = u;
      pathCapacity[v] = MIN(pathCapacity[u], residualCapacity);
      if(v != t)
	q.push(v);
      else
	return pathCapacity[t];
    }    
  }

  return 0;
}

/*
Edmonds-Karp: https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm
 */
int main() {
  int n, s, t, c, n1, n2, b;
  int capacityMatrix[10000], flowMatrix[10000];
  Neighbours edges[100];
  int prev[100];

  for(int cas = 1; true; ++cas) {
    std::cin >> n;
    if(n == 0)
      return 0;
    for(int i = 0; i < n; ++i) {
      edges[i].clear();
      for(int j = 0; j < n; ++j)
	capacityMatrix[i*n+j] = flowMatrix[i*n+j] = 0;
    }

    std::cin >> s >> t >> c;
    --s;
    --t;
    for(int i = 0; i < c; ++i) {
      std::cin >> n1 >> n2 >> b;
      --n1;
      --n2;
      if(edges[n1].find(n2) == edges[n1].end()) {
        edges[n1].insert(n2);
        edges[n2].insert(n1);
      }
      capacityMatrix[n1*n+n2] += b;
      capacityMatrix[n2*n+n1] += b;
    }

    int bandwidth = 0;
    int add;
    while((add = BFS(s, t, n, edges, prev, capacityMatrix, flowMatrix)) > 0) {
      //std::cerr << "Adding flow with capacity " << add << ": " << t;
      bandwidth += add;
      int v = t;
      while(v != s) {
	int u = prev[v];
	//std::cerr << "->" << u;
	flowMatrix[n*u+v] += add;
	flowMatrix[n*v+u] -= add;    
	v = u;
      }
      //std::cerr << std::endl;
    }
    
    std::cout << "Network " << cas << std::endl;
    std::cout << "The bandwidth is " << bandwidth << "." << std::endl;
    std::cout << std::endl;
  }  
}
