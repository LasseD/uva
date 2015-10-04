#include <iostream>
#include <limits>
#include <vector>
#include <set>

typedef std::pair<int,int> WeightAndVertex;
typedef std::pair<int,int> Edge;
typedef std::pair<int,Edge> WeightAndEdge;

#define INF std::numeric_limits<int>::max()
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

/*
Dijkstra for widest path. 
N vertices
R edges
 */
int dijkstra(int N, std::vector<WeightAndVertex> *adjacencyLists, int source, int destination) {
  //std::cerr << "Dijkstra(|V|=" << N << ",source=" << source << ",destination=" << destination << ")" << std::endl;
  if(source == destination)
    return INF;

  bool *visited = new bool[N];
  int *maxFlow = new int[N];
  for(int i = 0; i < N; ++i) {
    visited[i] = false;
    maxFlow[i] = 0;
  }
  maxFlow[source] = INF;
  visited[source] = true;

  std::set<WeightAndEdge> pool;
  // Fill pool for source:
  for(std::vector<WeightAndVertex>::const_iterator it = adjacencyLists[source].begin(); it != adjacencyLists[source].end(); ++it) {
    int neighbour = it->second;
    int neighbourEdgeWeight = it->first;
    pool.insert(WeightAndEdge(-neighbourEdgeWeight,Edge(source,neighbour)));
  }

  while(!pool.empty()) {
    const WeightAndEdge weightAndEdge = *pool.begin();
    pool.erase(pool.begin());
    const Edge &edge = weightAndEdge.second;
    const int from = edge.first;
    const int to = edge.second;
    const int weight = -weightAndEdge.first;

    if(visited[to])
      continue;
    visited[to] = true;
    // perform relaxation:
    //std::cerr << " " << from << "->" << to << " w=" << weight << " => increased from " << maxFlow[to] << " to ";
    maxFlow[to] = MIN(maxFlow[from], weight);
    //std::cerr << maxFlow[to] << std::endl;
    for(std::vector<WeightAndVertex>::const_iterator it = adjacencyLists[to].begin(); it != adjacencyLists[to].end(); ++it) {
      int neighbour = it->second;
      int neighbourEdgeWeight = it->first;
      if(visited[neighbour]) {
	if(maxFlow[neighbour] < MIN(maxFlow[to], neighbourEdgeWeight)) {
	  //std::cerr << "  " << to << "-->" << neighbour << " w=" << neighbourEdgeWeight << " => increased from " << maxFlow[neighbour] << " to ";
	  maxFlow[neighbour] = MIN(maxFlow[to], neighbourEdgeWeight); // LOL: Not even needed!
	  //std::cerr << maxFlow[neighbour] << std::endl;
	}
      }
      else {
	pool.insert(WeightAndEdge(-neighbourEdgeWeight,Edge(to,neighbour)));
      }
    }

    if(to == destination)
      break; // done!
  }

  delete[] visited;
  int ret = maxFlow[destination];
  delete[] maxFlow;
  return ret;
}

/*
  Widest path problem / the bottleneck shortest path problem
 */
int main() {
  int scenarioNumber = 1;
  while(true) {
    // Parse input:
    int N, R, S, D, T;
    std::cin >> N >> R; // Cities(vertices) and road segments(edges)
    if(N == 0 && R == 0)
      return 0;

    std::vector<WeightAndVertex> *adjacencyLists = new std::vector<WeightAndVertex>[N];

    for(int i = 0; i < R; ++i) {
      int C1, C2, P;
      std::cin >> C1 >> C2 >> P; // City, city, flow
      --C1;
      --C2;
      adjacencyLists[C1].push_back(WeightAndVertex(P, C2));
      adjacencyLists[C2].push_back(WeightAndVertex(P, C1));
    }
    std::cin >> S >> D >> T; // source, destination, number of tourists (total flow)
    --S;
    --D;    
    
    // Find maximum flow path between S and D:
    int maxFlow = dijkstra(N, adjacencyLists, S, D)-1; // -1 because tour guide is on the bus as well.
    delete[] adjacencyLists;

    // Compute result:
    std::cout << "Scenario #" << (scenarioNumber++) << std::endl;
    std::cout << "Minimum Number of Trips = " << ((T+maxFlow-1)/maxFlow) << std::endl << std::endl;
  }
}
