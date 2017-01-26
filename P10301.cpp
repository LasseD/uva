double dist(const Point2D &a, const Point2D &b) {
  double dx = a.XX-b.XX;
  double dy = a.YY-b.YY;
  return sqrt(dx*dx+dy*dy);
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

int main() {
  int N, parents[100], ranks[100], sizes[100];
  Point2D positions[100];
  double radius[100];
  while(true) {
    cin >> N;
    if(N == -1)
      return 0;

    FORI(N) {
      ranks[i] = sizes[i] = 0;
      parents[i] = i;
    }

    // Read input:
    FORI(N) {
      cin >> positions[i].XX >> positions[i].YY >> radius[i];
      double r1 = radius[i];
      for(int j = 0; j < i; ++j) {
	double d = dist(positions[i], positions[j]);
	double r2 = radius[j];
	if(d > r1+r2) {
	  //cerr << "NO TOUCH " << i << " "<< j << endl;
	  continue; // Not even touching.
	}
	if(r2 > d+r1 || r1 > d+r2) {
	  //cerr << "INSIDE " << i << " " << j << ", dist=" << d << ", r0=" << r1 <<", r1=" << r2 << endl;
	  continue; // Inside, but not touching.
	}
	//cerr << "Join " << i << " and " << j << endl;
	_union(i, j, parents, ranks);
      }
    }

    int max = 0;
    FORI(N) {
      int k = find(i, parents);
      ++sizes[k];
      if(sizes[k] > max)
	max = sizes[k];
    }
    if(max == 1)
      printf("The largest component contains 1 ring.\n");
    else
      printf("The largest component contains %d rings.\n", max);
  }
  return 0;
}
