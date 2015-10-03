#include <iostream>
#include <sstream>
#include <stdio.h>
#include <cmath>

typedef std::pair<double,double> Point;
typedef std::pair<Point,Point> Line;
#define X first
#define Y second
#define P1 first
#define P2 second
#define EPS_PRINT 0.0000001

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
  
  double s, t;
  double det = -s2.X * s1.Y + s1.X * s2.Y;
  if(det == 0)
    return false;
  s = (-s1.Y * (p0.X - p2.X) + s1.X * (p0.Y - p2.Y)) / det;
  t = ( s2.X * (p0.Y - p2.Y) - s2.Y * (p0.X - p2.X)) / det;
  
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

char sign(double d) {
  if(d < 0)
    return '-';
  return '+';
}

/*
  (x-h)^2 + (y-k)^2 = r^2 =>
  x^2 -2hx + h^2 + y^2 - 2ky + k^2 = r^2 =>
  x^2 + y^2 - 2hx -2ky + (h^2+k^2-r^2) = 0
*/
void print1(Point i, double r) {
  double h = i.X;
  double k = i.Y;

  if(std::abs(h) < EPS_PRINT)
  printf("x^2");
  else
    printf("(x %c %.3f)^2", sign(-h), std::abs(h));

  printf(" + ");

  if(std::abs(k) < EPS_PRINT)
  printf("y^2");
  else
    printf("(y %c %.3f)^2", sign(-k), std::abs(k));  

  printf(" = ");

  if(std::abs(r) < EPS_PRINT)
  printf("0\n");
  else
    printf("%.3f^2\n", r);

  double hx = - 2 * h;
  double ky = - 2 * k;
  double e = h*h+k*k-r*r;
  printf("x^2 + y^2 ");
  if(std::abs(hx) >= EPS_PRINT)
    printf("%c %.3fx ", sign(hx), std::abs(hx));
  if(std::abs(ky) >= EPS_PRINT)
    printf("%c %.3fy ", sign(ky), std::abs(ky));
  if(std::abs(e) >= EPS_PRINT)
    printf("%c %.3f ", sign(e), std::abs(e));
  printf("= 0\n");
}

int main() {
  bool first = true;
  std::string line;
  while(getline(std::cin, line)) {
    std::stringstream ss(line);
    Point input[3];
    for(int i = 0; i < 3; ++i)
      ss >> input[i].X >> input[i].Y;

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

    print1(intersection, radius);
    printf("\n");
  }
  return 0;
}
