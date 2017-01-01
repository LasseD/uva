#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>

using namespace std;

typedef pair<int,int> PP;
typedef pair<long,PP> DPP;
#define X first
#define Y second

long distSq(const PP &a, const PP &b) {
  return (a.X-b.X)*(a.X-b.X) + (a.Y-b.Y)*(a.Y-b.Y);
}

int find(int x, int *parents) {
  if(parents[x] != x)
    parents[x] = find(parents[x], parents);
  return parents[x];
}

bool _union(int x, int y, int *parents, int *ranks) {
  int xRoot = find(x, parents);
  int yRoot = find(y, parents);
  if(xRoot == yRoot)
    return false;

  // x and y are not already in same set. Merge them.
  if(ranks[xRoot] < ranks[yRoot])
    parents[xRoot] = yRoot;
  else if(ranks[xRoot] > ranks[yRoot])
    parents[yRoot] = xRoot;
  else {
    parents[yRoot] = xRoot;
    ++ranks[xRoot];
  }
  return true;
}

int main() {
  int N, S, P, parents[500], ranks[500];
  PP positions[500];
  DPP *dists = new DPP[500*500];
  cin >> N;
  for(int cas = 0; cas < N; ++cas) {
    // Read input:
    cin >> S >> P;
    for(int i = 0; i < P; ++i) {
      cin >> positions[i].X >> positions[i].Y;
    }
    // Compute dists:
    int distsI = 0;
    for(int i = 0; i < P; ++i)
      for(int j = i+1; j < P; ++j)
	dists[distsI++] = DPP(distSq(positions[i], positions[j]), PP(i,j));
    sort(dists, dists+distsI);

    // Prepare Union-find structure (parents and ranks):
    for(int i = 0; i < P; ++i) {
      ranks[i] = 0;
      parents[i] = i;
    }
    int trees = P;
    long DD = 0;
    distsI = 0;
    //cerr << "Starting tree merging. trees=P=" << P << endl;
    while(trees > S && trees > 1) {
      int x = dists[distsI].second.X;
      int y = dists[distsI].second.Y;
      DD = dists[distsI].first;
      ++distsI;
      if(_union(x, y, parents, ranks))
	--trees;
    }
    printf("%.2f\n", sqrt(DD));
  }
  return 0;
}
