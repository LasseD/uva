typedef PI WeightAndVertex;

#define INF numeric_limits<int>::max()

/*
Dijkstra for shortest path. 
N vertices
M edges
 */
int dijkstra(int N, int width, int height, int *M, int source, int destination) {
  //cerr << "Dijkstra(|V|=" << N << ",source=" << source << ",destination=" << destination << ")" << endl;
  if(source == destination) {
    return M[source];
  }

  bool *visited = new bool[N];
  int *minPath = new int[N];
  for(int i = 0; i < N; ++i) {
    visited[i] = false;
    minPath[i] = INF;
  }
  minPath[source] = M[source];

  set<WeightAndVertex> Q; // To visit
  Q.insert(WeightAndVertex(M[source], source));

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

    int y = from / width;
    int x = from % width;
    for(int y2 = y-1; y2 <= y+1; ++y2) {
      if(y2 < 0 || y2 >= height)
	continue;
      int x2 = x;
      if(x2 < 0 || x2 >= width)
	continue;
	
      int neighbour = y2*width+x2;
      if(visited[neighbour])
	continue;

      int neighbourWeight = weight + M[neighbour];
      if(minPath[neighbour] <= neighbourWeight)
	continue;
      //cerr << "  " << from << "-->" << neighbour << " w=" << M[neighbour] << " => from " << minPath[neighbour] << " to " << neighbourWeight << endl;
      minPath[neighbour] = neighbourWeight;
      Q.insert(WeightAndVertex(neighbourWeight, neighbour));
    }
    for(int x2 = x-1; x2 <= x+1; ++x2) {
      if(x2 < 0 || x2 >= width)
	continue;
      int y2 = y;
	
      int neighbour = y2*width+x2;
      if(visited[neighbour])
	continue;

      int neighbourWeight = weight + M[neighbour];
      if(minPath[neighbour] <= neighbourWeight)
	continue;
      //cerr << "  " << from << "-->" << neighbour << " w=" << M[neighbour] << " => from " << minPath[neighbour] << " to " << neighbourWeight << endl;
      minPath[neighbour] = neighbourWeight;
      Q.insert(WeightAndVertex(neighbourWeight, neighbour));
    }
  }

  int ret = minPath[destination];
  delete[] visited;
  delete[] minPath;
  return ret;
}

/*
  Widest path problem / the bottleneck shortest path problem
 */
int main() {
  int N, w, h;

  FORCAS {
    cin >> h >> w;
    N = h*w;
    int *M = new int[w*h];
    FORY(h) {
      FORX(w) {
	cin >> M[y*w+x];
      }
    }
    cout << dijkstra(N, w, h, M, 0, N-1) << endl;
    delete[] M;
  }
  return 0;
}
