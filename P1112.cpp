typedef pair<int,int> WeightAndVertex;

#define INF numeric_limits<int>::max()

/*
Dijkstra for shortest path. 
N vertices
 */
int dijkstra(int N, vector<WeightAndVertex> *adjacencyLists, int source, int limit) {
  //cerr << "Dijkstra(|V|=" << N << ",source=" << source << ",destination=" << destination << ")" << endl;

  bool *visited = new bool[N];
  int *minPath = new int[N];
  int ret = 0;
  
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
    ++ret;
    const int weight = p.first;

    // perform relaxation:
    //cerr << " " << from << " w=" << weight << " => relax from " << minPath[from] << " to " << weight << endl;
    visited[from] = true;

    for(vector<WeightAndVertex>::const_iterator it = adjacencyLists[from].begin(); it != adjacencyLists[from].end(); ++it) {
      int neighbour = it->second;
      if(visited[neighbour])
	continue;

      int neighbourWeight = weight + it->first;
      if(minPath[neighbour] <= neighbourWeight || neighbourWeight > limit)
	continue;
      //cerr << "  " << from << "-->" << neighbour << " w=" << it->first << " => from " << minPath[neighbour] << " to " << neighbourWeight << endl;
      minPath[neighbour] = neighbourWeight;
      Q.insert(WeightAndVertex(neighbourWeight, neighbour));
    }
  }

  delete[] visited;
  delete[] minPath;
  return ret;
}

/*
  Simple application of Dijkstra to compute total number of vertices within reach of source (exit).
 */
int main() {
  vector<WeightAndVertex> adjacencyLists[101];
  int N, M, s, t, w, exit, limit; // N nodes, M edges

  FORCAS {
    if(cas > 0)
      cout << endl;
    cin >> N >> exit >> limit >> M; --exit;
    FORI(N) {
      adjacencyLists[i].clear();
    }
    FORI(M) {
      cin >> t >> s >> w; --s; --t;
      adjacencyLists[s].push_back(WeightAndVertex(w,t));
    }
    cout << dijkstra(N, adjacencyLists, exit, limit) << endl;
  }
}
