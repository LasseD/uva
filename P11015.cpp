typedef pair<int,int> WeightAndVertex;

#define INF numeric_limits<int>::max()

/*
Dijkstra for shortest path. 
N vertices
 */
int dijkstraMaxDist(int N, vector<WeightAndVertex> *adjacencyLists, int source) {
  bool *visited = new bool[N];
  int *minPath = new int[N];
  FORI(N) {
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
    visited[from] = true;

    FORIT(vector<WeightAndVertex>, adjacencyLists[from]) {
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

  int ret = 0;
  FORI(N) {
    ret += minPath[i];
  }
  delete[] visited;
  delete[] minPath;
  return ret;
}

int main() {
  vector<WeightAndVertex> adjacencyLists[23];
  string name;
  int N, M, s, t, w;
  for(int cas = 0; true; ++cas) {
    cin >> N;
    if(N == 0)
      return 0;
    cin >> M;
    vector<string> names;
    FORI(N) {
      adjacencyLists[i].clear();
      cin >> name; 
      names.push_back(name);
    }
    FORI(M) {
      cin >> s >> t >> w; --s; --t;
      adjacencyLists[s].push_back(WeightAndVertex(w, t));
      adjacencyLists[t].push_back(WeightAndVertex(w, s));
    }
    
    // Find maximum flow path between S and D:
    int min = INF;
    FORI(N) {
      int m = dijkstraMaxDist(N, adjacencyLists, i);
      if(m < min) {
	min = m;
	name = names[i];
      }
    }
    cout << "Case #" << cas+1 << " : " << name << endl;
  }
}
