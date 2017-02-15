typedef pair<int,int> WeightAndVertex;

#define INF numeric_limits<int>::max()

/*
Dijkstra for shortest path. 
N vertices
 */
void dijkstra(int N, vector<WeightAndVertex> *adjacencyLists, int source, int *minPath) {
  //cerr << "Dijkstra(|V|=" << N << ",source=" << source << ",destination=" << destination << ")" << endl;

  bool *visited = new bool[N];
  //int *minPath = new int[N];
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
      Q.insert(WeightAndVertex(neighbourWeight, neighbour));
    }
  }

  delete[] visited;
}

/*
  Widest path problem / the bottleneck shortest path problem
 */
int main() {
  vector<WeightAndVertex> adjacencyLists[101];
  int N, M, s, t, minS[101], minT[101]; // N nodes, M edges

  FORCAS {
    cin >> N >> M;
    FORI(N) {
      adjacencyLists[i].clear();
    }
    FORI(M) {
      cin >> s >> t;
      adjacencyLists[s].push_back(WeightAndVertex(1,t));
      adjacencyLists[t].push_back(WeightAndVertex(1,s));
    }
    cin >> s >> t;
    
    // Find maximum flow path between S and D:
    dijkstra(N, adjacencyLists, s, minS);
    dijkstra(N, adjacencyLists, t, minT);
    int max = 0;
    FORI(N) {
      int x = minS[i]+minT[i];
      //cerr << "STEPPING " << i << ": " << minS[i]<<"+"<<minT[i] << "=" << x << endl;
      max = MAX(x, max);
    }
    
    cout << "Case " << cas+1 << ": " << max << endl;
  }
}
