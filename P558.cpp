#include <iostream>
#include <stdio.h>
#include <vector>
#include <limits>

#define INF std::numeric_limits<int>::max()
typedef std::pair<int,int> Edge;
typedef std::pair<Edge,int> WEdge;

/*
Algorithm from https://en.wikipedia.org/wiki/Bellman-Ford_algorithm
Predecessor array removed from this implementation.
 */
bool BellmanFordForNegativeCycleDetection(int n, const std::vector<WEdge> edges) {
  // Step 1: initialize graph
  int distance[1000];
  for(int i = 0; i < n; ++i)
    distance[i] = INF;
  distance[0] = 0; // Source is 0.
  
  // Step 2: relax edges repeatedly
  for(int i = 0; i < n; ++i) {
    bool anyImprovement = false;
    for(std::vector<WEdge>::const_iterator it = edges.begin(); it != edges.end(); ++it) {
      const WEdge &we = *it;
      const Edge &e = we.first;
      int u = e.first;
      int v = e.second;
      int w = we.second;
      if(distance[u] + w < distance[v]) {
	distance[v] = distance[u] + w;
	anyImprovement = true;
      }
    }
    if(!anyImprovement)
      return false; // no cycle.
  }

  // Step 3: check for negative-weight cycles by repeating the loop:
  for(std::vector<WEdge>::const_iterator it = edges.begin(); it != edges.end(); ++it) {
    const WEdge &we = *it;
    const Edge &e = we.first;
    int u = e.first;
    int v = e.second;
    int w = we.second;
    if(distance[u] + w < distance[v])
      return true;
  }
  return false;
}

/*
Use Bellman-Ford to detect negative weight cycles by performing an additional iteration. If there is a negative weight cycle, then the iteration will cause a change:
https://en.wikipedia.org/wiki/Bellman-Ford_algorithm#Finding_negative_cycles
 */
int main() {
  int c, n, m, x, y, t;
  std::cin >> c;
  for(int cas = 0; cas < c; ++cas) {
    std::vector<WEdge> edges;

    std::cin >> n >> m; // Nodes n, edges m.
    for(int i = 0; i < m; ++i) {
      std::cin >> x >> y >> t; // edge(x,y) with weight t.
      edges.push_back(WEdge(Edge(x, y), t));
    }
    if(BellmanFordForNegativeCycleDetection(n, edges))
      std::cout << "possible" << std::endl;
    else
      std::cout << "not possible" << std::endl;
  }
  return 0;
}
