typedef pair<int,PI> Edge;

int find(int x, int *parents) {
  if(parents[x] != x)
    parents[x] = find(parents[x], parents);
  return parents[x];
}

bool _union(int x, int y, int *parents, int *ranks, bool skip) {
  int xRoot = find(x, parents);
  int yRoot = find(y, parents);
  if(xRoot == yRoot)
    return false;
  if(skip)
    return true;

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

int main() {
  int N, M, a, b, c;
  int parents[100];
  int ranks[100];

  FORCAS {
    // Read data:
    cin >> N >> M; 
    vector<Edge> edges;
    FORI(M) {
      cin >> a >> b >> c; --a; --b;
      edges.push_back(Edge(c, PI(a,b)));
    }
    sort(edges.begin(), edges.end());

    // Prepare Union-find structure (parents and ranks):
    FORI(N) {
      ranks[i] = 0;
      parents[i] = i;
    }
    // Compute minimal price:
    int cost = 0;
    int size = 0;
    FORI(M) {
      Edge &e = edges[i];
      PI p = e.second;
      if(_union(p.P1, p.P2, parents, ranks, false)) {
	cost += e.first;
	++size;
	if(size == N-1)
	  break;
      }
    }

    // Output cheapest plan:
    cout << cost << " ";
    
    // Find maximum flow path between S and D:
    int min = 2000000000;
    for(int skip = 0; skip < N-1; ++skip) {
      size = 0;
      int m = 0; // new cost
      // Prepare Union-find structure (parents and ranks):
      FORI(N) {
	ranks[i] = 0;
	parents[i] = i;
      }
      // Run:
      FORI(M) {
	Edge &e = edges[i];
	PI p = e.second;
	if(_union(p.P1, p.P2, parents, ranks, skip == size)) {
	  if(skip != size) {
	    m += e.first; // Only count edge when actually added.
	  }
	  ++size;
	  if(size == N)
	    break;
	}
      }
      //cerr << "Run " << skip << ": " << m << endl;
      if(size == N && m < min) {
	min = m;
	if(min == cost)
	  break;
      }
    }
    
    if(2000000000 == min)
      die();
    cout << min << endl;
  }
}
