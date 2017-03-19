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
  //vector<WeightAndVertex> adjacencyLists[401];
  int parents[401], ranks[401];
  WPI edges[79801];
  string name, name2;
  int N, M, s, t, w;
  while(true) {
    cin >> N >> M;
    if(N == 0 && M == 0)
      return 0;
    map<string,int> names;
    FORI(N) {
      ranks[i] = 0;
      parents[i] = i;
      cin >> name; 
      names.insert(make_pair(name, (int)names.size()));
    }
    FORI(M) {
      cin >> name >> name2 >> w;
      s = names[name];
      t = names[name2];
      edges[i] = WPI(w, PI(s,t));
    }
    sort(edges, edges+M);
    cin >> name;
    
    int sum = 0;
    FORI(M) {
      w = edges[i].first;
      PI p = edges[i].second;
      if(_union(p.P1, p.P2, parents, ranks)) {
	sum += w;
      }
    }
    s = find(names[name], parents);
    FORI(N) {
      if(find(i, parents) != s) {
	sum = -1;
	break;
      }
    }

    // Find maximum flow path between S and D:
    if(sum == -1)
      cout << "Impossible" << endl;
    else
      cout << sum << endl;
  }
}
