#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>

#define X first
#define Y second
typedef std::pair<double,double> Point;
typedef std::vector<Point> Vector;

#define INF 1e12
#define MIN(a,b) ((a)<(b)?(a):(b))

double distSq(const Point &p1, const Point &p2) {
  return (p1.X-p2.X)*(p1.X-p2.X)+(p1.Y-p2.Y)*(p1.Y-p2.Y);
}

double closestPairDistSq(Point const * const pts, int N) {
  if(N <= 1)
    return INF;
  if(N == 2)
    return distSq(pts[0], pts[1]);
  int midIndex = N/2;
  double left = closestPairDistSq(pts, midIndex+1);
  double right = closestPairDistSq(&pts[midIndex], N-midIndex);
  double min = MIN(left,right);

  Vector vLeft, vRight;
  double midX = pts[midIndex].X;
  for(int i = 0; i < midIndex; ++i) {
    if((midX-pts[i].X)*(midX-pts[i].X) <= min)
      vLeft.push_back(pts[i]);
  }
  for(int i = midIndex; i < N; ++i) {
    if((-midX+pts[i].X)*(-midX+pts[i].X) <= min)
      vRight.push_back(pts[i]);
  }
  for(unsigned int i = 0; i < vLeft.size(); ++i) {
    for(unsigned int j = 0; j < vRight.size(); ++j) {
      min = MIN(min, distSq(vLeft[i], vRight[j]));
    }
  }
  return min;
}

int main() {
  int N;
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    Point *pts = new Point[N];
    for(int i = 0; i < N; ++i) {
      std::cin >> pts[i].X >> pts[i].second;
    }
    std::sort(pts, pts+N);
    double minDist = sqrt(closestPairDistSq(pts, N));
    if(minDist >= 10000-1e-5)
      printf("INFINITY\n");
    else
      printf("%.4lf\n", minDist);
    delete[] pts;
  }
}
