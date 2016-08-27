#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>

typedef std::pair<int,int> PP;
typedef std::pair<long,PP> DPP;
#define X first
#define Y second

long distSq(PP a, PP b) {
  return (a.X-b.X)*(a.X-b.X) + (a.Y-b.Y)*(a.Y-b.Y);
}

unsigned int find(unsigned int i, unsigned int *uf) {
  unsigned int store = i;
  while(i != uf[i])
    i = uf[i];
  unsigned int j = store;
  while(i != j) {
    store = uf[j]; // next.
    uf[j] = i;
    j = store; // stored next.
  }
  return i;
}

void _union(unsigned int i, unsigned int j, unsigned int *uf) {
  i = find(i, uf);
  j = find(j, uf);
  if(i == j)
    return;
  uf[i] = j;
}

int main() {
  unsigned int N, M, a, b, uf[750]; // n = number of buildings, m = existing connections.
  DPP *dists = new DPP[750*750];
  PP buildings[750];
  while(std::cin >> N) {
    for(unsigned int i = 0; i < N; ++i) {
      std::cin >> buildings[i].X >> buildings[i].Y;
      uf[i] = i;
    }

    std::cin >> M;
    for(unsigned int i = 0; i < M; ++i) {
      std::cin >> a >> b; --a; --b;
      _union(a, b, uf);      
    }

    int distsI = 0;
    for(unsigned int i = 0; i < N; ++i)
      for(unsigned int j = i+1; j < N; ++j)
	dists[distsI++] = DPP(distSq(buildings[i], buildings[j]), PP(i,j));
    std::sort(dists, dists+distsI);
    double ret = 0;
    for(int i = 0; i < distsI; ++i) {
      a = find(dists[i].second.first, uf);
      b = find(dists[i].second.second, uf);
      if(a == b)
	continue;
      _union(a, b, uf);      
      ret += sqrt(dists[i].first);
    }
    printf("%.2f\n", ret);
  }
  return 0;
}
