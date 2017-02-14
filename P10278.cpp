typedef PI WeightAndVertex;

#define INF numeric_limits<int>::max()

/*
Dijkstra for shortest path. 
N vertices
M edges
 */
int dijkstraMaxDist(int N, vector<WeightAndVertex> *adjacencyLists, vector<int> sources, int newSource) {
  //cerr << "Dijkstra(|V|=" << N << ",source=" << source << ",destination=" << destination << ")" << endl;
  bool *visited = new bool[N];
  int *minPath = new int[N];
  FORI(N) {
    visited[i] = false;
    minPath[i] = INF;
  }
  set<WeightAndVertex> Q; // To visit
  FORIT(vector<int>, sources) {
    minPath[*it] = 0;
    Q.insert(WeightAndVertex(0, *it));
  }
  minPath[newSource] = 0;
  Q.insert(WeightAndVertex(0, newSource));

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

    FORIT(vector<WeightAndVertex>, adjacencyLists[from]) {
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

  int max = 0;
  FORI(N) {
    if(minPath[i] > max)
      max = minPath[i];
  }
  delete[] visited;
  delete[] minPath;
  return max;
}

/*
  Widest path problem / the bottleneck shortest path problem
 */
int main() {
  string line;
  int f, N, s, t, w;
  vector<WeightAndVertex> adjacencyLists[501];
  getline(cin, line); // cases
  int cases = atoi(line.c_str());
  getline(cin, line); // empty line
  for(int cas = 0; cas < cases; ++cas) {
    if(cas > 0)
      cout << endl;
    getline(cin, line); // f and N.
    stringstream ss1; ss1 << line; ss1 >> f >> N;

    // Read fire stations:
    vector<int> fireStations;
    FORI(f) {
      getline(cin, line); // f and N.
      s = atoi(line.c_str()); --s;
      fireStations.push_back(s);
    }
    
    // Read intersections:
    FORI(N) {
      adjacencyLists[i].clear();
    }
    while(true) {
      getline(cin, line);
      if(cin.eof() || line.empty())
	break; // s t and w
      stringstream ss2; ss2 << line; 
      if(!(ss2 >> s >> t >> w))
	die();
      --s; --t;
      adjacencyLists[s].push_back(WeightAndVertex(w, t));
      adjacencyLists[t].push_back(WeightAndVertex(w, s));      
    }

    // Find result:
    int best = INF;
    int whereBest = 0;
    FORI(N) {
      int d = dijkstraMaxDist(N, adjacencyLists, fireStations, i);
      if(d < best) {
	best = d;
	whereBest = i;
      }
    }
    cout << whereBest+1 << endl;
  }
}
