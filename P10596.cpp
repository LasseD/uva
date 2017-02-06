typedef pair<int,int> Edge;
#define C1 first
#define C2 second

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

int main() {
  int parents[201], ranks[201], inDegrees[201];
  int N, R, c1, c2;

  while(cin >> N >> R) {
    // Reset memory:
    FORI(N) {
      ranks[i] = inDegrees[i] = 0;
      parents[i] = i;
    }
    int trees = N;

    // Read edges:
    FORI(R) {
      cin >> c1 >> c2;
      if(_union(c1, c2, parents, ranks))
	--trees;
      ++inDegrees[c1];
      ++inDegrees[c2];
    }

    FORI(N) {
      if(inDegrees[i] == 0)
	--trees; // Ignore all non-visited intersections.
    }

    FORI(N) {
      if(inDegrees[i] % 2 == 1) {
	trees = -1;
	//cerr << "Uneven degree!" << endl;
	break;
      }
    }

    if(trees == 1)
      cout << "Possible" << endl;
    else
      cout << "Not Possible" << endl;
  }
  return 0;
}
