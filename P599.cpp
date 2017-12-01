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
  int parents[26], ranks[26];
  bool graphs[26];
  int size[26];
  FORCAS {
    FORI(26) {
      graphs[i] = false;
      size[i] = 0;
      ranks[i] = 0;
      parents[i] = i;      
    }

    while(true) {
      GS(s);
      if(s[0] == '*')
	break;
      int a = s[1]-'A';
      int b = s[3]-'A';
      if(!_union(a, b, parents, ranks)) {
	graphs[a] = graphs[b] = true;
      }      
    }
    GS(s);
    int total = 0;
    for(int i = 0; i < (int)s.size(); i+=2) {
      ++total;
      int a = s[i]-'A';
      ++size[find(a, parents)];
      if(graphs[a])
	graphs[find(a, parents)] = true;
    }
    int cntTrees = 0;
    int cntAcorns = 0;
    FORI(26) {
      if(size[i] == 0)
	continue;
      else if(size[i] == 1)
	++cntAcorns;
      else if(!graphs[i])
	++cntTrees;
    }
    cout << "There are " << cntTrees << " tree(s) and " << cntAcorns << " acorn(s)." << endl;
  } // FORCAS
} // main
