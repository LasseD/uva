#include <iostream>
#include <stdio.h>

typedef std::pair<int,int> Point;
typedef std::pair<double,double> Point2D;
typedef std::pair<Point,Point> Line;
#define X first
#define P1 first
#define Y second
#define P2 second

bool rightTurn(int diffX, int diffY, int x1, int y1, const Point &p) {
  return diffX*(p.Y-y1) < diffY*(p.X-x1);
}
bool rightTurn(const Point &p1, const Point &p2, const Point &p) {
  return rightTurn(p2.X-p1.X, p2.Y-p1.Y, p2.X, p2.Y, p);
}

bool colinear(int diffX, int diffY, int x1, int y1, const Point &p) {
  return diffX*(p.Y-y1) == diffY*(p.X-x1);
}
bool colinear(const Point &p1, const Point &p2, const Point &p) {
  return colinear(p2.X-p1.X, p2.Y-p1.Y, p2.X, p2.Y, p);
}

bool overlap(const Line &a, const Line &b) {
  return colinear(a.X, a.Y, b.X) && colinear(a.X, a.Y, b.Y);
}

// Returns true if the lines intersect. 
// If the lines intersect, the intersection point may be stored in i.
bool getLineIntersection(Point p0, Point p1, Point p2, Point p3, Point2D &i) {
  Point s1, s2;
  s1.X = p1.X - p0.X;     
  s1.Y = p1.Y - p0.Y;
  s2.X = p3.X - p2.X;     
  s2.Y = p3.Y - p2.Y;
  
  double det = -s2.X * s1.Y + s1.X * s2.Y;
  if(det == 0)
    return false;
  double t = ( s2.X * (p0.Y - p2.Y) - s2.Y * (p0.X - p2.X)) / det;
  
  i = Point2D(p0.X + (t * s1.X), p0.Y + (t * s1.Y));
  return true;
}
bool getLineIntersection(Line l1, Line l2, Point2D &i) {
  return getLineIntersection(l1.P1, l1.P2, l2.P1, l2.P2, i);
}


int main() {
  printf("INTERSECTING LINES OUTPUT\n");
  int n;
  std::cin >> n;
  Point2D d;

  for(int i = 0; i < n; ++i) {
    Line l1, l2;
    std::cin >> l1.first.X >> l1.first.Y >> l1.second.X >> l1.second.Y;
    std::cin >> l2.first.X >> l2.first.Y >> l2.second.X >> l2.second.Y;

    if(overlap(l1, l2))
      printf("LINE\n");
    else if(getLineIntersection(l1, l2, d))
      printf("POINT %.2f %.2f\n", d.X, d.Y);
    else
      printf("NONE\n");
  }
  printf("END OF OUTPUT\n"); 
}
