#include <iostream>
#include <ctype.h>

#define IDX  10001
#define SIZE 100020001
typedef std::pair<int,int> point;

int main() {
  int g, n, m;
  std::cin >> g;
  bool *a = new bool[SIZE];
  for(int i = 0; i < SIZE; ++i) {
    a[i] = false;
  }
  point *points = new point[g];
  for(int i = 0; i < g; ++i) {
    std::cin >> n >> m;
    points[i] = point(n,m);
  }
  int sprinklers;
  std::cin >> sprinklers;  
  for(int i = 0; i < sprinklers; ++i) {
    int radius;
    std::cin >> n >> m >> radius;
    int startX = n - radius < 0 ? 0 : n-radius;
    for(int x = startX; x <= n+radius && x < IDX; ++x) {
      int startY = m - radius < 0 ? 0 : m-radius;
      for(int y = startY; y <= m+radius && y < IDX; ++y) {
	int dx = x-n;
	int dy = y-m;
	if((dx*dx+dy*dy) <= radius*radius) {
	  a[x*IDX+y] = true;
	}
      }
    }
  }

  int ret = 0;
  for(int i = 0; i < g; ++i) {
    point p = points[i];
    if(!a[p.first*IDX+p.second])
      ++ret;
  }
  std::cout << ret << std::endl;
}
