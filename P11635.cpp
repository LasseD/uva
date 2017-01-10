#include <iostream>
#include <limits>
#include <vector>
#include <set>

using namespace std;

typedef pair<int,int> WeightAndVertex;

#define INF numeric_limits<int>::max()
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

/*
Dijkstra for shortest path. 
N vertices
M edges
 */
void dijkstra(int N, vector<WeightAndVertex> const * const adjacencyLists, const vector<int> &sources, int maxPathLength, int * const minPath) {
  /*cerr << "Dijkstra(|V|=" << N << ",sources=";
  for(vector<int>::const_iterator it = sources.begin(); it != sources.end(); ++it)
    cerr << *it << ",";
  cerr << ")" << endl;//*/

  bool *visited = new bool[N];
  set<WeightAndVertex> Q; // To visit

  for(int i = 0; i < N; ++i) {
    visited[i] = false;
    minPath[i] = INF;
  }
  for(vector<int>::const_iterator it = sources.begin(); it != sources.end(); ++it) {
    int source = *it;
    minPath[source] = 0;
    Q.insert(WeightAndVertex(0, source));
  }

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
      if(minPath[neighbour] <= neighbourWeight || neighbourWeight > maxPathLength)
	continue;
      //cerr << "  " << from << "-->" << neighbour << " w=" << it->first << " => from " << minPath[neighbour] << " to " << neighbourWeight << endl;
      minPath[neighbour] = neighbourWeight;
      Q.insert(WeightAndVertex(neighbourWeight, neighbour));
    }
  }

  delete[] visited;
  //delete[] minPath;
}

/*
  Widest path problem / the bottleneck shortest path problem
 */
int main() {
  int n, h, c, m;
  while(true) {
    cin >> n;
    if(n == 0)
      return 0;

    set<int> hotels;
    cin >> h;
    for(int i = 0; i < h; ++i) {
      cin >> c;
      --c;
      hotels.insert(c);
    }

    vector<WeightAndVertex> *adjacencyLists = new vector<WeightAndVertex>[n];

    cin >> m;
    for(int i = 0; i < m; ++i) {
      int C1, C2, P;
      cin >> C1 >> C2 >> P; // a->b, weight
      --C1;
      --C2;
      adjacencyLists[C1].push_back(WeightAndVertex(P, C2));
      adjacencyLists[C2].push_back(WeightAndVertex(P, C1));
    }
    
    // Find maximum flow path between S and D:
    bool ok = false;
    int *minPath = new int[n];
    vector<int> sources;
    sources.push_back(0);
    for(int iterations = 0; true; ++iterations) {
      dijkstra(n, adjacencyLists, sources, 60*10, minPath);
      if(minPath[n-1] != INF) {
	cout << iterations << endl;
	ok = true;
	break;
      }
      sources.clear();
      for(set<int>::const_iterator it = hotels.begin(); it != hotels.end(); ++it) {
	int c = *it;
	if(minPath[c] == INF)
	  continue;
	sources.push_back(c);	
      }
      if(sources.empty())
	break;
      for(vector<int>::const_iterator it = sources.begin(); it != sources.end(); ++it) {
	int c = *it;
	if(hotels.find(c) != hotels.end())
	  hotels.erase(c);
      }
    }
    if(!ok)
      cout << -1 << endl;
    delete[] adjacencyLists;
    delete[] minPath;
  }
}
