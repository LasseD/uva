#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

typedef std::pair<int,int> Edge;
typedef std::pair<int,Edge> WeightAndEdge;

/*
Union find: Iterate through edges by weight and union vertices.
 */
void find(int n, int const * const tree, int &found, int &steps) {
  steps = 0;
  while(tree[n] != -1) {
    ++steps;
    n = tree[n];
  }
  found = n;
}

int lca(const int c1, const int c2, int const * const tree, bool *visited) {
  // Pollute for c1:
  int n = c1;
  while(n != -1) {
    visited[n] = true;
    n = tree[n];
  }
  // Find lca:
  n = c2;
  while(!visited[n])
    n = tree[n];

  int lca = n;

  // Cleanup:
  n = c1;
  while(n != -1) {
    visited[n] = false;
    n = tree[n];
  }

  return lca;
}

/*
  MST
 */
int main() {
  int N, M; // N vertices, M edges.
  while(std::cin >> N >> M) {
    if(N == 0 && M == 0)
      return 0;
    int *tree = new int[N];
    bool *visited = new bool[N];
    for(int i = 0; i < N; ++i) {
      tree[i] = -1;
      visited[i] = false;
    }

    long sumGraph = 0;
    // Read edges and build union-find tree:
    std::vector<WeightAndEdge> v;
    for(int i = 0; i < M; ++i) {
      int C1, C2, P;
      std::cin >> C1 >> C2 >> P; // a->b, weight
      sumGraph += P;
      v.push_back(WeightAndEdge(P, Edge(C1,C2)));
    }
    std::sort(v.begin(), v.end());

    int sumMST = 0;
    for(std::vector<WeightAndEdge>::const_iterator it = v.begin(); it != v.end(); ++it) {
      int C1 = it->second.first;
      int C2 = it->second.second;
      int P = it->first;
      int r1, r2, s1, s2;
      find(C1, tree, r1, s1);
      find(C2, tree, r2, s2);
      if(r1 != r2) {
	if(s1 > s2)
	  tree[r2] = r1;
	else
	  tree[r1] = r2;
	sumMST += P;
      }
    }
    std::cout << (sumGraph-sumMST) << std::endl;
    delete[] tree;
    delete[] visited;
  }
}
