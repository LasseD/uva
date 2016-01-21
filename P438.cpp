#include <iostream>
#include <stdio.h>
#include <cmath>

typedef std::pair<double,double> Point;
typedef std::pair<Point,Point> Line;
#define X first
#define Y second
#define P1 first
#define P2 second

std::ostream& operator<<(std::ostream& out, const Point& e){
  return out << "(" << e.X << "," << e.Y << ")";
}
std::ostream& operator<<(std::ostream& out, const Line& e){
  return out << e.P1 << "->" << e.P2;
}

double distSq(Point p1, Point p2) {
  return (p1.X-p2.X)*(p1.X-p2.X) + (p1.Y-p2.Y)*(p1.Y-p2.Y);
}
double dist(Point p1, Point p2) {
  return std::sqrt(distSq(p1, p2));
}

// Returns true if the lines intersect. 
// If the lines intersect, the intersection point may be stored in i.
bool getLineIntersection(Point p0, Point p1, Point p2, Point p3, Point &i) {
  Point s1, s2;
  s1.X = p1.X - p0.X;     
  s1.Y = p1.Y - p0.Y;
  s2.X = p3.X - p2.X;     
  s2.Y = p3.Y - p2.Y;
  
  double det = -s2.X * s1.Y + s1.X * s2.Y;
  if(det == 0)
    return false;
  double t = ( s2.X * (p0.Y - p2.Y) - s2.Y * (p0.X - p2.X)) / det;
  
  i = Point(p0.X + (t * s1.X), p0.Y + (t * s1.Y));
  return true;
}
bool getLineIntersection(Line l1, Line l2, Point &i) {
  return getLineIntersection(l1.P1, l1.P2, l2.P1, l2.P2, i);
}

Point mid(const Line &l) {
  double midX = (l.P1.X + l.P2.X)/2;
  double midY = (l.P1.Y + l.P2.Y)/2;
  return Point(midX, midY);
}
Point mid(const Point &p1, const Point &p2) {
  return mid(Line(p1, p2));
}

Line midTangent(const Line &l) {
  double midX = (l.P1.X + l.P2.X)/2;
  double midY = (l.P1.Y + l.P2.Y)/2;

  double dX = l.P2.X - l.P1.X;
  double dY = l.P2.Y - l.P1.Y;

  Point p1 = Point(midX, midY);
  Point p2 = Point(midX + dY, midY - dX);
  return Line(p1, p2);
}

int main() {
  Point input[3];
  while(std::cin >> input[0].X >> input[0].Y >> input[1].X >> input[1].Y >> input[2].X >> input[2].Y) {
    // find the tangents:
    Line lines[3];
    for(int i = 0; i < 3; ++i) {
      lines[i] = Line(input[i], input[(i+1)%3]);
    }

    Line tangents[3];
    for(int i = 0; i < 3; ++i) {
      tangents[i] = midTangent(lines[i]);
    }

    Point intersection;
    for(int i = 0; true; ++i) {
      if(getLineIntersection(tangents[i], tangents[(i+1)%3], intersection))
	break;
    }
    double radius = dist(input[0], intersection);

    printf("%.2f\n", radius*2*M_PI);
  }
  return 0;
}
