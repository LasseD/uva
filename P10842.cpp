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

typedef pair<int,PI> WPI;

int main() {
  int parents[101], ranks[101];
  WPI edges[10001];
  int N, M, s, t, w;
  FORCAS {
    cin >> N >> M;
    FORI(N) {
      ranks[i] = 0;
      parents[i] = i;
    }
    FORI(M) {
      cin >> s >> t >> w;
      edges[i] = WPI(-w, PI(s,t));
    }
    sort(edges, edges+M);
    
    int min = 1000000;
    FORI(M) {
      w = edges[i].first;
      PI p = edges[i].second;
      if(_union(p.P1, p.P2, parents, ranks)) {
	min = MIN(min, -w);
      }
    }
    cout << "Case #" << cas+1 << ": " << min << endl;
  }
}
