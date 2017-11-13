typedef PI WeightAndVertex;

#define INF numeric_limits<int>::max()

/*
Dijkstra for shortest path to all targets. 
N vertices
 */
void dijkstra(int N, vector<WeightAndVertex> *adjacencyLists, int source, int *minPath) {
  bool *visited = new bool[N];
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

  delete[] visited;
}

int main() {
  vector<WeightAndVertex> neighboursY[26], neighboursM[26];
  string a, b, c, d;
  int sM, sY, w, minPathY[26], minPathM[26];
  while(true) {
    GI(N);
    if(N == 0)
      return 0;

    FORI(26) {
      neighboursY[i].clear();
      neighboursM[i].clear();
    }

    FORI(N) {
      cin >> a >> b >> c >> d >> w;
      bool uni = b[0] == 'U';
      int s = c[0]-'A';
      int t = d[0]-'A';
      if(a[0] == 'Y') {
	neighboursY[s].push_back(WeightAndVertex(w, t));
	if(!uni)
	  neighboursY[t].push_back(WeightAndVertex(w, s));
      }
      else {
	neighboursM[s].push_back(WeightAndVertex(w, t));
	if(!uni)
	  neighboursM[t].push_back(WeightAndVertex(w, s));
      }
    }

    cin >> a >> b;
    sY = a[0]-'A';
    sM = b[0]-'A';

    dijkstra(26, neighboursM, sM, minPathM);
    dijkstra(26, neighboursY, sY, minPathY);

    // Output:
    int bestValue = INF;
    FORI(26) {
      if(minPathM[i] < INF && minPathY[i] < INF && minPathM[i]+minPathY[i] < bestValue)
	bestValue = minPathM[i]+minPathY[i];
    }
    if(bestValue == INF) {
      cout << "You will never meet." << endl;
    }
    else {
      cout << bestValue;
      FORI(26) {	
	if(minPathM[i] < INF && minPathY[i] < INF && minPathM[i]+minPathY[i] == bestValue)
	  cout << " " << (char)(i+'A');
      }
      cout << endl;
    }
    
  } // while true
} // int main
