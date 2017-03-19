long distSq(const Point &a, const Point &b) {
  long dx = a.XX-b.XX;
  long dy = a.YY-b.YY;
  return dx*dx+dy*dy;
}

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

typedef pair<long,PI> LPI;

int main() {
  int N, R, parents[1000], ranks[1000];
  Point positions[1000];

  FORCAS {
    cin >> N >> R;
    R *= R;
    vector<LPI> edges;
    FORI(N) {
      ranks[i] = 0;
      parents[i] = i;
      cin >> positions[i].XX >> positions[i].YY;
      FORJ(i) {
	edges.push_back(LPI(distSq(positions[i], positions[j]), PI(i, j)));
      }
    }
    sort(edges.begin(), edges.end());
    
    int states = N;
    double roads = 0, rail = 0;
    FORIT(vector<LPI>, edges) {
      if(it->first > R) {
	if(_union(it->second.P1, it->second.P2, parents, ranks)) {
	  rail += sqrt(it->first);
	}
      }
      else {
	if(_union(it->second.P1, it->second.P2, parents, ranks)) {
	  --states;
	  roads += sqrt(it->first);
	}
      }
    }
    printf("Case #%d: %d %.0lf %.0lf\n", cas+1, states, roads, rail);
  }
  return 0;
}
