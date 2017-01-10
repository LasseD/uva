#include <iostream>
#include <vector>

using namespace std;

typedef pair<int,int> PP;

#define MAX 25

/*
Algorithm: Count incident edges to all nodes. Once 0: Add to stack.
 */
int longestPath(int numVertices, vector<PP> const * const incident, int source, bool *visited) {
  int max = 0;
  for(vector<PP>::const_iterator it = incident[source].begin(); it != incident[source].end(); ++it) {
    PP edge = *it;
    if(!visited[edge.second]) {
      visited[edge.second] = true;
      int add = 1+longestPath(numVertices, incident, edge.first, visited);
      if(add > max)
	max = add;
      visited[edge.second] = false;
    }
  }
  return max;
}

/*
  Widest path problem / the bottleneck shortest path problem
 */
int main() {
  int n, m, p, q;
  vector<PP> incident[MAX];
  bool visited[MAX];
  for(int cas = 1; true; ++cas) {
    cin >> n >> m;
    if(n == 0 && m == 0)
      return 0;
    for(int i = 0; i < n; ++i) {
      incident[i].clear();
    }

    for(int i = 0; i < m; ++i) {
      cin >> p >> q;
      visited[i] = false;
      incident[p].push_back(PP(q,i));
      incident[q].push_back(PP(p,i));
    }

    int max = -1;
    for(int s = 0; s < n; ++s) {
      // Starting point s:
      int len = longestPath(n, incident, s, visited);
      if(len > max)
	max = len;
    }
    cout << max << endl;
  }
}
