struct Node {
  vector<int> in, out;
  bool visited;
  
  void reset() {
    in.clear();
    out.clear();
    visited = false;
  }
};

Node nodes[2001];

int dfs(int i) {
  nodes[i].visited = true;
  int ret = 1;
  FORIT(vector<int>, nodes[i].out) {
    if(nodes[*it].visited)
      continue;
    ret += dfs(*it);
  }
  return ret;
}

int main() {
  int N, M, a, b, c;
  while(true) {
    cin >> N >> M; // N nodes, M connections.
    if(N == 0 && M == 0)
      return 0;
    FORI(N)
      nodes[i].reset();
    // Build graph:
    FORI(M) {
      cin >> a >> b >> c;
      --a;
      --b; // 0-index
      nodes[a].out.push_back(b);
      nodes[b].in.push_back(a);
      if(c == 2) {
	nodes[b].out.push_back(a);
	nodes[a].in.push_back(b);
      }
    }
    // DFS from first node:
    int cntReachableFromFirst = dfs(0);
    //cerr << "N=" << N << endl;
    //cerr << "cntReachableFromFirst = " << cntReachableFromFirst << endl;
    if(cntReachableFromFirst != N) {
      cout << 0 << endl;
      continue;
    }
    stack<int> unhandledQ; // clique with first node.
    unhandledQ.push(0);
    int sizeQ = 0;
    while(!unhandledQ.empty()) {
      Node &n = nodes[unhandledQ.top()];
      unhandledQ.pop();
      if(!n.visited)
	continue;
      ++sizeQ;
      n.visited = false;
      FORIT(vector<int>, n.in) {
	if(!nodes[*it].visited)
	  continue;
	unhandledQ.push(*it);
      } // FORIT      
    } // while unhandled
    if(sizeQ == N)
      cout << 1 << endl;
    else
      cout << 0 << endl;
  }
}
