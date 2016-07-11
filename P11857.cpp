#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

typedef std::pair<int,int> WeightAndVertex;
typedef std::pair<int,int> Edge;
typedef std::pair<int,Edge> WeightAndEdge;

#define INF std::numeric_limits<int>::max()
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

/*
Union find: Iterate through edges by weight and union vertices.
 */
void find(int n, WeightAndVertex const * const tree, int &found, int &steps) {
  steps = 0;
  while(tree[n].second != -1) {
    ++steps;
    n = tree[n].second;
  }
  found = n;
}

int lca(const int c1, const int c2, WeightAndVertex const * const tree, bool *visited) {
  // Pollute for c1:
  int n = c1;
  while(n != -1) {
    visited[n] = true;
    n = tree[n].second;
  }
  // Find lca:
  n = c2;
  while(!visited[n]) {
    n = tree[n].second;
  }

  int lca = n;

  // Cleanup:
  n = c1;
  while(n != -1) {
    visited[n] = false;
    n = tree[n].second;
  }

  //std::cerr << "LCA(" << c1 << "," << c2 << ") = " << lca << std::endl;
  return lca;
}

/*
  Widest path problem / the bottleneck shortest path problem
 */
int main() {
  int N, M;
  int r1, r2, s1, s2;

  while(true) {
    std::cin >> N >> M;
    if(N == 0 && M == 0)
      return 0;
    WeightAndVertex *tree = new WeightAndVertex[N];
    bool *visited = new bool[N];
    for(int i = 0; i < N; ++i) {
      tree[i] = WeightAndVertex(INF,-1);
      visited[i] = false;
    }

    // Read edges and build union-find tree:
    std::vector<WeightAndEdge> v;
    for(int i = 0; i < M; ++i) {
      int C1, C2, P;
      std::cin >> C1 >> C2 >> P; // a->b, weight
      v.push_back(WeightAndEdge(P, Edge(C1,C2)));
    }
    std::sort(v.begin(), v.end());

    int maxS = 0;
    for(std::vector<WeightAndEdge>::const_iterator it = v.begin(); it != v.end(); ++it) {
      int C1 = it->second.first;
      int C2 = it->second.second;
      int P = it->first;
      find(C1, tree, r1, s1);
      find(C2, tree, r2, s2);
      //std::cerr << C1 << "<->" << C2 << ", unions " << r1 << " & " << r2 << ", weight: " << P << std::endl;
      if(r1 != r2) {
	if(s1 > s2)
	  tree[r2] = WeightAndVertex(P, r1);
	else
	  tree[r1] = WeightAndVertex(P, r2);
	maxS = P;
      }
    }

    bool connected = true;
    find(0, tree, r1, s1);
    for(int i = 1; connected && i < N; ++i) {
      find(i, tree, r2, s2);
      if(r1 != r2)
	connected = false;
    }
    if(connected)
      std::cout << maxS << std::endl;
    else
      std::cout << "IMPOSSIBLE" << std::endl;
    
    delete[] tree;
    delete[] visited;
  }
}
