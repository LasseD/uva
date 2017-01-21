typedef PI WeightAndVertex;
#define INF numeric_limits<int>::max()

/*
Dijkstra for shortest path. 
N vertices
M edges
 */
void dijkstra(int N, vector<int> *adjacencyLists, int source, int destination, stack<int> &path) {
  //cerr << "Dijkstra(|V|=" << N << ",source=" << source << ",destination=" << destination << ")" << endl;
  if(source == destination) {
    path.push(source);
    path.push(destination);
    return;
  }

  bool *visited = new bool[N];
  int *minPath = new int[N];
  int *prev = new int[N];
  for(int i = 0; i < N; ++i) {
    visited[i] = false;
    minPath[i] = INF;
  }
  minPath[source] = 0;

  set<WeightAndVertex> Q; // To visit
  Q.insert(WeightAndVertex(0, source));

  while(!Q.empty()) {
    const WeightAndVertex p = *Q.begin();
    Q.erase(Q.begin());
    const int from = p.second;
    if(visited[from])
      continue;
    const int weight = p.first;
    if(from == destination)
      break;

    // perform relaxation:
    //cerr << " " << from << " w=" << weight << " => relax from " << minPath[from] << " to " << weight << endl;
    visited[from] = true;

    for(vector<int>::const_iterator it = adjacencyLists[from].begin(); it != adjacencyLists[from].end(); ++it) {
      int neighbour = *it;
      if(visited[neighbour])
	continue;

      int neighbourWeight = weight + 1;
      if(minPath[neighbour] <= neighbourWeight)
	continue;
      //cerr << "  " << from << "-->" << neighbour << " w=1" << " => from " << minPath[neighbour] << " to " << neighbourWeight << endl;
      minPath[neighbour] = neighbourWeight;
      prev[neighbour] = from;
      Q.insert(WeightAndVertex(neighbourWeight, neighbour));
    }
  }

  if(minPath[destination] != INF) {
    path.push(destination);
    int pos = destination;
    while(source != (pos = prev[pos])) {
      path.push(pos);
      path.push(pos);
    }
    path.push(source);
  }

  delete[] visited;
  delete[] minPath;
  delete[] prev;
}

/*
  Widest path problem / the bottleneck shortest path problem
 */
int main() {
  int M, s, t;
  string s1, s2;
  bool first = true;
  while(cin >> M) {
    if(!first)
      cout << endl;
    first = false;
    vector<int> *adjacencyLists = new vector<int>[2*M+2]; // At most 2M cities!
    map<string,int> m;
    map<int,string> rev;
    FORI(M) {
      cin >> s1 >> s2;
      if(m.find(s1) == m.end()) {
	m.insert(PSI(s1, (int)m.size()));
	rev.insert(PIS((int)rev.size(), s1));
      }
      if(m.find(s2) == m.end()) {
	m.insert(PSI(s2, (int)m.size()));
	rev.insert(PIS((int)rev.size(), s2));
      }
      s = m[s1];
      t = m[s2];
      adjacencyLists[s].push_back(t);
      adjacencyLists[t].push_back(s);
    }
    // query:
    cin >> s1 >> s2;
    if(m.find(s1) == m.end()) {
      m.insert(PSI(s1, (int)m.size()));
      rev.insert(PIS((int)rev.size(), s1));
    }
    if(m.find(s2) == m.end()) {
      m.insert(PSI(s2, (int)m.size()));
      rev.insert(PIS((int)rev.size(), s2));
    }
    s = m[s1];
    t = m[s2];
    
    // Find maximum flow path between S and D:
    stack<int> path;
    dijkstra((int)m.size(), adjacencyLists, s, t, path);
    delete[] adjacencyLists;

    // Compute result:
    if(path.empty())
      cout << "No route" << endl;
    else {
      while(!path.empty()) {
	cout << rev[path.top()] << " ";
	path.pop();
	cout << rev[path.top()] << endl;
	path.pop();
      }
    }
  }
} 
