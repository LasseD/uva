int find(int x, int *parents) {
  if(parents[x] != x)
    parents[x] = find(parents[x], parents);
  return parents[x];
}

bool _union(int x, int y, int *parents, int *ranks) {
  int xRoot = find(x, parents);
  int yRoot = find(y, parents);
  if(xRoot == yRoot)
    return false;

  // x and y are not already in same set. Merge them.
  if(ranks[xRoot] < ranks[yRoot])
    parents[xRoot] = yRoot;
  else if(ranks[xRoot] > ranks[yRoot])
    parents[yRoot] = xRoot;
  else {
    parents[yRoot] = xRoot;
    ++ranks[xRoot];
  }
  return true;
}

typedef pair<long,PI> Edge;

int main() {
  int N, M, a, b, w, parents[1000], ranks[1000];
  Edge edges[25000];
  while(true) {
    cin >> N >> M;
    if(N == 0 && M == 0)
      return 0;
    FORI(M) {
      cin >> a >> b >> w;
      edges[i] = Edge(w, PI(a,b));
    }
    sort(edges, edges+M);
    bool first = true;

    // Prepare Union-find structure (parents and ranks):
    FORI(N) {
      ranks[i] = 0;
      parents[i] = i;
    }
    FORI(M) {
      PI p = edges[i].second;
      if(!_union(p.P1, p.P2, parents, ranks)) {
	if(!first)
	  cout << " ";
	first = false;
	cout << edges[i].first;
      }
    }
    if(first)
      cout << "forest";
    cout << endl;
  } // while true
} // main
