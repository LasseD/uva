typedef PI WeightAndVertex;

#define INF numeric_limits<int>::max()

/*
Dijkstra for shortest path. 
N vertices
M edges
 */
void dijkstra(int N, vector<WeightAndVertex> *adjacencyLists, int source, int destination) {
  //cerr << "Dijkstra(|V|=" << N << ",source=" << source << ",destination=" << destination << ")" << endl;
  if(source == destination) {
    cout << source+1 << "; 0 second delay" << endl;
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
  prev[source] = source;

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

    for(vector<WeightAndVertex>::const_iterator it = adjacencyLists[from].begin(); it != adjacencyLists[from].end(); ++it) {
      int neighbour = it->second;
      if(visited[neighbour])
	continue;

      int neighbourWeight = weight + it->first;
      if(minPath[neighbour] <= neighbourWeight)
	continue;
      //cerr << "  " << from << "-->" << neighbour << " w=" << it->first << " => from " << minPath[neighbour] << " to " << neighbourWeight << endl;
      minPath[neighbour] = neighbourWeight;
      prev[neighbour] = from;
      Q.insert(WeightAndVertex(neighbourWeight, neighbour));
    }
  }

  int ret = minPath[destination];
  // Stack:
  stack<int> st;
  int curr = destination;
  while(prev[curr] != curr) {
    st.push(curr);
    curr = prev[curr];
  }
  // Output:
  cout << source+1;
  while(!st.empty()) {
    cout << " " << st.top()+1;
    st.pop();
  }
  cout << "; " << ret << " second delay" << endl;

  delete[] visited;
  delete[] minPath;
  delete[] prev;
}

/*
  Widest path problem / the bottleneck shortest path problem
 */
int main() {
  int N, m, s, t, w;
  vector<WeightAndVertex> adjacencyLists[11];

  for(int cas = 1; true; ++cas) {
    cin >> N;
    if(N == 0)
      return 0;
    cout << "Case " << cas << ": Path = ";
    FORI(N) {
      adjacencyLists[i].clear();
      cin >> m;
      FORJ(m) {
	cin >> t >> w; --t;
	adjacencyLists[i].push_back(WeightAndVertex(w, t));
      }
    }
    cin >> s >> t; --s; --t;
    dijkstra(N, adjacencyLists, s, t);
  }
}
