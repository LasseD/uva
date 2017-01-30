void push(const int firstPushed, bool * const up, PI const * const edges, int const * const edgeStarts, const int m, int &cnt) {
  stack<int> s;
  s.push(firstPushed);

  while(!s.empty()) {
    int next = s.top();
    s.pop();
    if(!up[next])
      continue;
    up[next] = false; // Push over.
    ++cnt;
    int j = edgeStarts[next];
    if(j == -1)
      continue;
    while(j < m && edges[j].first == next) {
      if(up[edges[j].second])
	s.push(edges[j].second);
      ++j;
    }
  }
}

int main() {
  int n, m, L, x, y;
  FORCAS {
    cin >> n >> m >> L; // dominoes, unions, pushes
    PI *edges = new PI[m];
    int *edgeStarts = new int[n];
    bool *up = new bool[n];
    FORI(n) {
      up[i] = true;
      edgeStarts[i] = -1;
    }
    FORI(m) {
      cin >> x >> y; --x; --y;
      edges[i] = PI(x, y);
    }
    sort(edges, edges+m);
    int prev = -1;
    FORI(m) {
      if(prev != edges[i].first) {
	prev = edges[i].first;
	edgeStarts[prev] = i;
      }
    }

    int ret = 0;
    FORI(L) {
      cin >> x; --x;
      push(x, up, edges, edgeStarts, m, ret);
    }
    cout << ret << endl;

    delete[] edgeStarts;
    delete[] edges;
    delete[] up;
  }
  return 0;
}
