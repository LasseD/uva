typedef PI WeightAndVertex;

#define INF -1

/*
Dijkstra for shortest path. 
N vertices
M edges
 */
int dijkstra(int N, std::vector<WeightAndVertex> *adjacencyLists, int source) {
  bool *visited = new bool[N];
  unsigned int *minPath = new unsigned int[N];
  for(int i = 0; i < N; ++i) {
    visited[i] = false;
    minPath[i] = -1;
  }
  minPath[source] = 0;
  int max = 0;

  std::set<WeightAndVertex> Q; // To visit
  Q.insert(WeightAndVertex(0, source));

  while(!Q.empty()) {
    const WeightAndVertex p = *Q.begin();
    Q.erase(Q.begin());
    const int from = p.second;
    if(visited[from])
      continue;
    const int weight = p.first;

    // perform relaxation:
    visited[from] = true;
    if(weight > max)
      max = weight;

    for(std::vector<WeightAndVertex>::const_iterator it = adjacencyLists[from].begin(); it != adjacencyLists[from].end(); ++it) {
      int neighbour = it->second;
      if(visited[neighbour])
	continue;

      int neighbourWeight = weight + it->first;
      if(minPath[neighbour] <= neighbourWeight)
	continue;
      minPath[neighbour] = neighbourWeight;
      Q.insert(WeightAndVertex(neighbourWeight, neighbour));
    }
  }

  delete[] visited;
  delete[] minPath;
  return max;
}

/*
  Widest path problem / the bottleneck shortest path problem
 */
int main() {
  int N;
  string cost;;
  while(std::cin >> N) {
    std::vector<WeightAndVertex> *adjacencyLists = new std::vector<WeightAndVertex>[N];

    FORI(N) {
      FORJ(i) {
	cin >> cost;
	if(cost[0] == 'x')
	  continue;
	int c = atoi(cost.c_str());
	adjacencyLists[i].push_back(WeightAndVertex(c, j));
	adjacencyLists[j].push_back(WeightAndVertex(c, i));
      }
    }

    cout << dijkstra(N, adjacencyLists, 0) << endl;
    delete[] adjacencyLists;
  }
  return 0;
}
