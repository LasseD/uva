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
  bool first = true;
  int N, M, K, a, b, w;
  while(cin >> N) { // site 1..N
    if(!first)
      cout << endl;
    first = false;
    int *parents = new int[N];
    int *ranks = new int[N];
    Edge *edges = new Edge[N+10];

    long cost = 0;
    FORI(N-1) {
      cin >> a >> b >> w; --a; --b;
      cost += w;
      edges[i] = Edge(w, PI(a,b));      
    }
    cout << cost << endl;
    cost = 0;
    cin >> K;
    FORI(K) {
      cin >> a >> b >> w; --a; --b;
      edges[N-1+i] = Edge(w, PI(a,b));
    }
    cin >> M;
    FORI(M) {
      cin >> a >> b >> w; // Ignore.
    }
    sort(edges, edges+N-1+K);

    // Prepare Union-find structure (parents and ranks):
    FORI(N) {
      ranks[i] = 0;
      parents[i] = i;
    }
    FORI(M) {
      PI p = edges[i].second;
      if(_union(p.P1, p.P2, parents, ranks)) {
	cost += edges[i].first;
      }
    }
    cout << cost << endl;

    delete[] parents;
    delete[] ranks;
    delete[] edges;
  } // while true
} // main
