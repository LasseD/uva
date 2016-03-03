#include <iostream>
#include <limits>
#include <vector>
#include <set>

typedef std::pair<int,int> WeightAndVertex;

#define INF std::numeric_limits<int>::max()
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

/*
Dijkstra for shortest path. 
N vertices
M edges
 */
int dijkstra(int N, std::vector<WeightAndVertex> *adjacencyLists, int source, int destination) {
  //std::cerr << "Dijkstra(|V|=" << N << ",source=" << source << ",destination=" << destination << ")" << std::endl;
  if(source == destination)
    return 0;

  bool *visited = new bool[N];
  int *minPath = new int[N];
  for(int i = 0; i < N; ++i) {
    visited[i] = false;
    minPath[i] = INF;
  }
  minPath[source] = 0;

  std::set<WeightAndVertex> Q; // To visit
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
    //std::cerr << " " << from << " w=" << weight << " => relax from " << minPath[from] << " to " << weight << std::endl;
    visited[from] = true;

    for(std::vector<WeightAndVertex>::const_iterator it = adjacencyLists[from].begin(); it != adjacencyLists[from].end(); ++it) {
      int neighbour = it->second;
      if(visited[neighbour])
	continue;

      int neighbourWeight = weight + it->first;
      if(minPath[neighbour] <= neighbourWeight)
	continue;
      //std::cerr << "  " << from << "-->" << neighbour << " w=" << it->first << " => from " << minPath[neighbour] << " to " << neighbourWeight << std::endl;
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
  int N, n, m, s, t;
  std::cin >> N;
  for(int cas = 1; cas <= N; ++cas) {
    std::cin >> n >> m >> s >> t;

    std::vector<WeightAndVertex> *adjacencyLists = new std::vector<WeightAndVertex>[n];

    for(int i = 0; i < m; ++i) {
      int C1, C2, P;
      std::cin >> C1 >> C2 >> P; // a->b, weight
      adjacencyLists[C1].push_back(WeightAndVertex(P, C2));
      adjacencyLists[C2].push_back(WeightAndVertex(P, C1));
    }
    
    // Find maximum flow path between S and D:
    int minPath = dijkstra(n, adjacencyLists, s, t);
    delete[] adjacencyLists;

    // Compute result:
    if(minPath == INF)
      std::cout << "Case #" << cas << ": unreachable" << std::endl;
    else
      std::cout << "Case #" << cas << ": " << minPath << std::endl;
  }
}
