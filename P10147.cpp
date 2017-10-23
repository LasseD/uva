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
  PI positions[751];
  int parents[751], ranks[751];
  
  int N, M;
  FORCAS {
    if(cas > 0)
      cout << endl;

    cin >> N;
    
    // Prepare Union-find structure (parents and ranks):
    FORI(N) {
      ranks[i] = 0;
      parents[i] = i;
    }

    vector<Edge> edges;

    FORI(N) {
      cin >> positions[i].XX >> positions[i].YY;
    }

    cin >> M;
    FORI(M) {
      int a, b;
      cin >> a >> b; --a; --b;
      _union(a, b, parents, ranks);
    }

    FORI(N) {
      for(int j = 0; j < i; ++j) {
	if(find(i, parents) != find(j, parents)) {
	  PI pa = positions[i];
	  PI pb = positions[j];
	  long dx = pa.XX-pb.XX;
	  long dy = pa.YY-pb.YY;
	  long w = dx*dx+dy*dy;
	  edges.push_back(Edge(w, PI(j, i)));
	}
      }
    }

    sort(edges.begin(), edges.end());

    bool any = false;
    FORIT(vector<Edge>, edges) {
      const Edge &e = *it;
      PI p = e.second;
      if(_union(p.P1, p.P2, parents, ranks)) {
	cout << p.P1+1 << " " << p.P2+1 << endl;
	any = true;
      }      
    }
    if(!any)
      cout << "No new highways need" << endl;
  } // FORCAS
} // main
