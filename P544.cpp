#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <map>

typedef std::pair<int,int> WeightAndVertex;
typedef std::pair<int,int> Edge;
typedef std::pair<int,Edge> WeightAndEdge;
typedef std::string String;
typedef std::map<String,int> Map;

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
  int n, r;
  for(int cas = 1; true; ++cas) {
    std::cin >> n >> r;
    if(n == 0 && r == 0)
      return 0;

    WeightAndVertex *tree = new WeightAndVertex[n];
    bool *visited = new bool[n];
    for(int i = 0; i < n; ++i) {
      tree[i] = WeightAndVertex(INF,-1);
      visited[i] = false;
    }

    // Read edges and build union-find tree:
    std::vector<WeightAndEdge> v;
    Map s;

    String C1, C2;
    for(int i = 0; i < r; ++i) {
      int P;
      std::cin >> C1 >> C2 >> P; // a->b, weight
      if(s.find(C1) == s.end())
	s.insert(std::make_pair(C1, (int)s.size()));
      if(s.find(C2) == s.end())
	s.insert(std::make_pair(C2, (int)s.size()));
      v.push_back(WeightAndEdge(-P, Edge(s[C1],s[C2])));
    }
    std::sort(v.begin(), v.end());

    for(std::vector<WeightAndEdge>::const_iterator it = v.begin(); it != v.end(); ++it) {
      int C1 = it->second.first;
      int C2 = it->second.second;
      int P = -it->first;
      int r1, r2, s1, s2;
      find(C1, tree, r1, s1);
      find(C2, tree, r2, s2);
      //std::cerr << C1 << "<->" << C2 << ", unions " << r1 << " & " << r2 << ", weight: " << P << std::endl;
      if(r1 != r2) {
	if(s1 > s2)
	  tree[r2] = WeightAndVertex(P, r1);
	else
	  tree[r1] = WeightAndVertex(P, r2);
      }
    }

    // Handle query:
    std::cin >> C1 >> C2; // a->b, weight
    int from = s[C1];
    int to = s[C2];    

    int ca = lca(from, to, tree, visited);
    int min = INF;
    while(from != ca) {
      if(min > tree[from].first)
	min = tree[from].first;
      from = tree[from].second;
    }
    while(to != ca) {
      if(min > tree[to].first)
	min = tree[to].first;
      to = tree[to].second;
    }
    std::cout << "Scenario #" << cas << std::endl;      
    std::cout << min << " tons" << std::endl;      
    std::cout << std::endl;      
    
    delete[] tree;
    delete[] visited;
  }
}
