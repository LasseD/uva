#include <iostream>
#include <stack>
#include <algorithm>

typedef std::pair<int,int> PP;

#define MAX_EDGES 2000
#define MAX_VERTICES 1000

/*
Algorithm: Count incident edges to all nodes. Once 0: Add to stack.
 */
void longestPath(int numVertices, PP *edges, int numEdges, int source) {
  int longestPath = 0;
  int longestPathVertex = source;

  PP *edgeListIndicators = new PP[numVertices]; // vertex index -> first edge,num edges
  int *pathLengths = new int[numVertices]; // path lengths
  int *incidentCounts = new int[numVertices]; // incident edges.
  for(int i = 0; i < numVertices; ++i) {
    incidentCounts[i] = edgeListIndicators[i].second = 0; // Empty list.
    pathLengths[i] = (i == source) ? 0 : -99999;
  }
  std::sort(edges, edges+numEdges);
  int prevVertex = -1;
  for(int i = 0; i < numEdges; ++i) {
    if(edges[i].first != prevVertex) {
      prevVertex = edges[i].first;
      edgeListIndicators[prevVertex].second = 1;
      edgeListIndicators[prevVertex].first = i;
    }
    else
      ++edgeListIndicators[prevVertex].second;
    ++incidentCounts[edges[i].second];
  }

  std::stack<int> s;
  for(int i = 0; i < numVertices; ++i) {
    //std::cerr << "Incident to " << (i+1) << ": " << incidentCounts[i] << std::endl;
    //std::cerr << "Outgoing edges: |" << edgeListIndicators[i].second << "| from position " << edgeListIndicators[i].first << std::endl;
    if(incidentCounts[i] == 0) {
      s.push(i); // All empty lists.
    }
  }

  while(!s.empty()) {
    int cur = s.top();
    s.pop();
    if(pathLengths[cur] > longestPath || (pathLengths[cur] == longestPath && cur < longestPathVertex)) {
      longestPath = pathLengths[cur];
      longestPathVertex = cur;
    }
    // Decrease all incident counters. Add new 0's to stack:
    for(int i = 0; i < edgeListIndicators[cur].second; ++i) {
      PP &e = edges[edgeListIndicators[cur].first+i];
      --incidentCounts[e.second];
      if(1+pathLengths[cur] > pathLengths[e.second])
	pathLengths[e.second] = 1+pathLengths[cur];
      if(incidentCounts[e.second] == 0)
	s.push(e.second);
    }
  }

  delete[] edgeListIndicators;
  delete[] pathLengths;
  delete[] incidentCounts;
  std::cout << "The longest path from " << (source+1) << " has length " << longestPath << ", finishing at " << (longestPathVertex+1) << "." << std::endl << std::endl;
}

/*
  Widest path problem / the bottleneck shortest path problem
 */
int main() {
  int n, s, p, q;
  PP edges[MAX_EDGES];
  for(int cas = 1; true; ++cas) {
    std::cin >> n;
    if(n == 0)
      return 0;
    std::cout << "Case " << cas << ": ";

    // Parse input:
    std::cin >> s; // starting point.
    --s;

    int numEdges = 0;
    for(; true; ++numEdges) {
      std::cin >> p >> q;
      if(p == 0 && q == 0)
	break;
      --p;
      --q;
      edges[numEdges] = PP(p,q);
    }    
    // Find min path:
    longestPath(n, edges, numEdges, s);
  }
}
