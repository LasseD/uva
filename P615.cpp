int main() {
  int x, y;
  for(int cas = 1; true; ++cas) {
    // Read edges:
    set<int> nodes;
    vector<PI> edges;
    vector<PI> redges;
    bool tree = true;
    while(true) {
      cin >> x >> y;
      if(x < 0 && y < 0)
	return 0;
      if(x == 0 && y == 0)
	break;
      edges.push_back(PI(x,y));
      redges.push_back(PI(y,x));
      if(nodes.find(x) == nodes.end())
	nodes.insert(x);
      if(nodes.find(y) == nodes.end())
	nodes.insert(y);
      if(x == y) {
	tree = false;
	//cerr << "Node pointing to itself: " << x << "->" << y << endl;
      }
    }
    if(edges.empty()) {
      cout << "Case " << cas << " is a tree." << endl;    
      continue;
    }

    sort(edges.begin(), edges.end());
    sort(redges.begin(), redges.end());
    map<int,int> edgeStarts, redgeStarts;
    int prev = -1;
    FORUI(edges.size()) {
      if(edges[i].first != prev) {
	edgeStarts[edges[i].first] = (int)i;
	prev = edges[i].first;
      }
    }
    int rprev = -1;
    FORUI(redges.size()) {
      if(redges[i].first != rprev) {
	redgeStarts[redges[i].first] = (int)i;
	rprev = redges[i].first;
      }
    }
    // Find root:
    int root = *nodes.begin();
    set<int> marked;
    marked.insert(root);
    while(tree && redgeStarts.find(root) != redgeStarts.end()) {
      root = redges[redgeStarts[root]].second;
      if(marked.find(root) != marked.end()) {
	tree = false;
	//cerr << "Cycle found while searching for root: " << root << endl;
      }
    }
    // Color full tree:
    marked.clear();
    stack<int> s;
    s.push(root);
    while(tree && !s.empty()) {
      int node = s.top();
      s.pop();
      if(marked.find(node) != marked.end()) {
	tree = false; // already visited!
	//cerr << "Cycle found while visiting all nodes: " << node << endl;
	break;
      }
      marked.insert(node);
      if(edgeStarts.find(node) == edgeStarts.end())
	continue;
      int start = edgeStarts[node];
      for(int i = start; i < (int)edges.size() && edges[i].first == node; ++i) {
	s.push(edges[i].second);
      }
    }
    if(tree) {
      if(marked.size() != nodes.size()) {
	tree = false;
	//cerr << "Not all nodes visited: " << nodes.size() << " vs " << marked.size() << endl;
      }
    }
    cout << "Case " << cas << " is ";
    if(!tree)
      cout << "not ";
    cout << "a tree." << endl;    
  }
}
