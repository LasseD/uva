#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>

typedef std::pair<int,int> Point;
#define X first
#define Y second

int main() {
  int C, N;
  Point prev;

  std::cin >> C;
  for(int cas = 0; cas < C; ++cas) {
    std::cin >> N;
    Point *v = new Point[N];
    for(int i = 0; i < N; ++i) {
      std::cin >> v[i].X >> v[i].Y;
      v[i].X = -v[i].X;
    }
    std::sort(v, v+N);
    prev = v[0];

    double ret = 0;
    int maxY = 0;
    for(int i = 1; i < N; ++i) {
      Point &p = v[i];
      Point &prev = v[i-1];
      if(p.Y > maxY) {
	ret += sqrt((p.Y-prev.Y)*(p.Y-prev.Y)+(p.X-prev.X)*(p.X-prev.X)) * (p.Y-maxY)/((double)(p.Y-prev.Y));
	  
	maxY = p.Y;
      }
    }
    printf("%.2f\n", ret);
  }
  return 0;
}
