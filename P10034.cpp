#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <cmath>

typedef std::pair<double,double> Pt;
typedef std::pair<double,int> WEdge;
typedef std::set<WEdge> set;

double dist(const Pt &a, const Pt &b) {
  return sqrt((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}

int main() {
  Pt pts[100];
  bool handled[100];

  int cases, N;
  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    if(cas > 0)
      printf("\n");

    // Read and setup data:
    std::cin >> N;
    for(int i = 0; i < N; ++i) {
      std::cin >> pts[i].first >> pts[i].second;
      handled[i] = false;
    }

    double sum = 0;
    int numHandled = 0;
    set s;
    s.insert(WEdge(0, 0));
    while(numHandled < N) {
      WEdge min = *s.begin();
      s.erase(min);
      if(handled[min.second])
	continue;
      sum += min.first;
      handled[min.second] = true;
      ++numHandled;
      for(int i = 0; i < N; ++i) {
	if(handled[i])
	  continue;
	s.insert(WEdge(dist(pts[i],pts[min.second]), i));
      }
    } // while(numHandled < N)
    printf("%.2f\n", sum);
  } // for case
  return 0;
}
