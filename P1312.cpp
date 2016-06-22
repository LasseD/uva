#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstdlib>

#define X first
#define Y second

typedef std::pair<int,int> Point;
typedef std::vector<Point> Vector;

void maxArea(const Vector &v, int xMin, int yMin, int xMax, int yMax, int &P, int &Q, int &L) {
  if(v.empty()) {
    int side = xMax-xMin;
    if(yMax-yMin < side)
      side = yMax-yMin;
    if(L >= side)
      return;
    L = side;
    P = xMin;
    Q = yMin;
    return;
  }
  Point pivot = v[0];
  Vector vTop, vBottom, vLeft, vRight;
  for(unsigned int i = 1; i < v.size(); ++i) {
    Point p = v[i];
    if(p.X > pivot.X)
      vRight.push_back(p);
    else
      vLeft.push_back(p);
    if(p.Y > pivot.Y)
      vTop.push_back(p);
    else
      vBottom.push_back(p);
  }
  maxArea(vTop, xMin, pivot.Y, xMax, yMax, P, Q, L);
  maxArea(vBottom, xMin, yMin, xMax, pivot.Y, P, Q, L);
  maxArea(vLeft, xMin, yMin, pivot.X, yMax, P, Q, L);
  maxArea(vRight, pivot.X, yMin, xMax, yMax, P, Q, L);
}

int main () {
  int cases, N, W, H, x, y, P, Q, L;
  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      std::cout << std::endl;
    std::cin >> N >> W >> H;
    Vector v;
    for(int i = 0; i < N; ++i) {
      std::cin >> x >> y;
      v.push_back(Point(x, y));
    }
    std::random_shuffle(v.begin(), v.end());
    L = 0;
    maxArea(v, 0, 0, W, H, P, Q, L);
    std::cout << P << " " << Q << " " << L << std::endl;
  }
  return 0;
}
