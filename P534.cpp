#include <iostream>
#include <stdio.h>
#include <set>
#include <cmath>

#define X first
#define Y second
typedef std::pair<int,int> Pair;
typedef std::pair<int,Pair> DistPair;
typedef std::set<DistPair> Set;

#define MAX(a,b) ((a) < (b) ? (b) : (a))

int distSq(int a, int b, Pair *stones) {
  Pair &pA = stones[a];
  Pair &pB = stones[b];
  return (pA.X-pB.X)*(pA.X-pB.X) + (pA.Y-pB.Y)*(pA.Y-pB.Y);
}

int main() {
  int n;
  Pair stones[200];
  bool visited[200];
  int dist[200];

  for(int cas = 1; true; ++cas) {
    std::cin >> n;
    if(n == 0)
      return 0;
    for(int i = 0; i < n; ++i)
      std::cin >> stones[i].X >> stones[i].Y;
    visited[0] = true;
    dist[0] = 0;
    for(int i = 1; i < n; ++i)
      visited[i] = false;

    Set s;
    
    for(int i = 1; i < n; ++i)
      s.insert(DistPair(distSq(0, i, stones), Pair(0,i)));

    while(true) {
      DistPair p = *s.begin();
      s.erase(s.begin());
      int stone = p.second.second;
      if(visited[stone])
	continue;
      visited[stone] = true;
      dist[stone] = MAX(dist[p.second.first], p.first);

      if(stone == 1) { // Fiona!
	printf("Scenario #%d\nFrog Distance = %.3f\n\n", cas, 1e-6+sqrt(dist[stone]));
	break;
      }
      for(int i = 0; i < n; ++i) {
	if(!visited[i])
	  s.insert(DistPair(distSq(stone, i, stones), Pair(stone,i)));
      }
    }
  }
}
