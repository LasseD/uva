#include <iostream>

typedef std::pair<int,int> Point;
typedef std::pair<Point,Point> Line;
#define x first
#define y second

bool rightTurn(int diffX, int diffY, int x1, int y1, const Point &p) {
  return diffX*(p.y-y1) < diffY*(p.x-x1);
}
bool rightTurn(const Point &p1, const Point &p2, const Point &p) {
  return rightTurn(p2.x-p1.x, p2.y-p1.y, p2.x, p2.y, p);
}
bool colinear(int diffX, int diffY, int x1, int y1, const Point &p) {
  return diffX*(p.y-y1) == diffY*(p.x-x1);
}
bool colinear(const Point &p1, const Point &p2, const Point &p) {
  return colinear(p2.x-p1.x, p2.y-p1.y, p2.x, p2.y, p);
}
bool cross(const Line &a, const Line &b) {
  if(colinear(a.x, a.y, b.x) || colinear(a.x, a.y, b.y)) {
    return rightTurn(b.x, b.y, a.x) != rightTurn(b.x, b.y, a.y);
  }
  if(colinear(b.x,b.y,a.x) || colinear(b.x,b.y,a.y)) {
    return rightTurn(a.x, a.y, b.x) != rightTurn(a.x, a.y, b.y);
  }

  return rightTurn(a.x, a.y, b.x) != rightTurn(a.x, a.y, b.y) && 
         rightTurn(b.x, b.y, a.x) != rightTurn(b.x, b.y, a.y);
}

int main() {
  int n;
  std::cin >> n;
  for(int i = 0; i < n; ++i) {
    Line l;
    std::cin >> l.first.x >> l.first.y >> l.second.x >> l.second.y;
    int x1, x2, y1, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    if(x1 > x2)
      std::swap(x1,x2);
    if(y1 > y2)
      std::swap(y1,y2);
    if(x1 <= l.first.x && x2 >= l.first.x && y1 <= l.first.y && y2 >= l.first.y) {
      std::cout << "T" << std::endl;
      continue;
    }
    if(x1 <= l.second.x && x2 >= l.second.x && y1 <= l.second.y && y2 >= l.second.y) {
      std::cout << "T" << std::endl;
      continue;
    }
 
    Point p1, p2, p3, p4;
    p1 = Point(x1, y1);
    p2 = Point(x1, y2);
    p3 = Point(x2, y2);
    p4 = Point(x2, y1);
    Line r1, r2, r3, r4;
    r1 = Line(p1, p2);
    r2 = Line(p2, p3);
    r3 = Line(p3, p4);
    r4 = Line(p4, p1);
    if(cross(r1,l) || cross(r2,l) || cross(r3,l) || cross(r4,l)) {
      std::cout << "T" << std::endl;
    }
    else {
      std::cout << "F" << std::endl;
    }
  }
}
