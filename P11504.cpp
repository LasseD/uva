// Cormen/Tarjan: https://en.wikipedia.org/wiki/Topological_sorting
void visit(stack<int> &L, const int n, bool * const marked, bool * const temporaryMarked, PI const * const edges, int const * const edgeStarts, const int m) {
  //cerr << "Visiting " << n << endl;
  if(temporaryMarked[n])
    return; // if n has a temporary mark then stop (not a DAG)
  if(marked[n])
    return; // if n is not marked (i.e. has not been visited yet) then:
  temporaryMarked[n] = true; // mark n temporarily
  
  /*        
        for each node m with an edge from n to m do
            visit(m)
  */
  int j = edgeStarts[n];
  if(j != -1) {
    while(j < m && edges[j].first == n) {
      visit(L, edges[j].second, marked, temporaryMarked, edges, edgeStarts, m);
      ++j;
    }
  }

  marked[n] = true; // mark n permanently
  temporaryMarked[n] = false; // unmark n temporarily
  //cerr << "Topo sorted: " << n << endl;
  L.push(n); // add n to head of L
}
void topoSortUsingDFS(stack<int> &L, const int n, PI const * const edges, int const * const edgeStarts, const int m) {
  bool *marked = new bool[n];
  bool *temporaryMarked = new bool[n];
  memset(marked, false, n*sizeof(bool));
  memset(temporaryMarked, false, n*sizeof(bool));
  FORI(n) {
    if(marked[i])
      continue;
    visit(L, i, marked, temporaryMarked, edges, edgeStarts, m);
  }
  delete[] marked;
  delete[] temporaryMarked;
}

void push(const int firstPushed, bool * const up, PI const * const edges, int const * const edgeStarts, const int m) {
  stack<int> s;
  s.push(firstPushed);

  while(!s.empty()) {
    int next = s.top();
    s.pop();
    if(!up[next])
      continue;
    up[next] = false; // Push over.
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
  int n, m, x, y;
  FORCAS {
    cin >> n >> m; // dominoes, unions
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

    stack<int> L;
    topoSortUsingDFS(L, n, edges, edgeStarts, m);

    int ret = 0;
    while(!L.empty()) { //FORIT(stack<int>, L) {
      int t = L.top(); L.pop();
      if(!up[t])
	continue;
      ++ret;
      push(t, up, edges, edgeStarts, m);      
    }
    cout << ret << endl;

    delete[] edgeStarts;
    delete[] edges;
    delete[] up;
  }
  return 0;
}
