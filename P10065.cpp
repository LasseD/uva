#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Geometry:
typedef std::pair<int,int> Point;
typedef std::pair<double,double> Point2D;
typedef std::pair<Point,Point> Line;
typedef std::vector<Line> LineVector;
typedef std::vector<Point> Polygon;
#define X first
#define P1 first
#define Y second
#define P2 second
// Event points:
struct EventPoint; // Forward declaration.
typedef std::set<EventPoint> EventQueue;
typedef std::vector<Line> SweepLine;
#define START 2
#define END 0
#define CROSS 1

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << "(" << p.X << "," << p.Y << ")";
  return os;
}
std::ostream& operator<<(std::ostream& os, const Line& line) {
  os << line.P1 << "->" << line.P2;
  return os;
}
std::ostream& operator<<(std::ostream& os, const Polygon& p) {
  if(p.empty())
    return os;
  os << p[0];
  for(unsigned int i = 1; i < p.size(); ++i)
    os << "->" << p[i];
  return os;
}

/*
 * Convex hull represented bY a list of points in clockwise order.
 */
bool rightTurn(const Point &lineStart, const Point &lineEnd, const Point &p) {
  return (lineEnd.X-lineStart.X)*(p.Y-lineStart.Y) - (lineEnd.Y-lineStart.Y)*(p.X-lineStart.X) < 0;
}
bool leftTurn(const Point &lineStart, const Point &lineEnd, const Point &p) {
  return (lineEnd.X-lineStart.X)*(p.Y-lineStart.Y) - (lineEnd.Y-lineStart.Y)*(p.X-lineStart.X) > 0;
}
/*bool colinear(const Point &lineStart, const Point &lineEnd, const Point &p) {
  return (lineEnd.X-lineStart.X)*(p.Y-lineStart.Y) - (lineEnd.Y-lineStart.Y)*(p.X-lineStart.X) == 0;
}*/
Point flipY(const Point &b) {
  return Point(b.X, -b.Y);
}
bool epsEq(double a, double b) {
  if(b < a)
    return epsEq(b, a);
  return b-a < 1e-6;
}
bool epsEq(const Point2D &a, const Point &b) {
  return epsEq(a.X, b.X) && epsEq(a.Y, b.Y);
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

struct ConvexHull {
  Point *points;
  int size;
			   		
  Polygon upperHull(const Point &left, const Point &right, Polygon &between) {
    between.push_back(right);
    
    Polygon out;
    out.push_back(left);
    Point lastPeek = right;
    for(Polygon::const_iterator it = between.begin(); it != between.end(); ++it) {
      if(it->X == lastPeek.X) {
	if(it->Y < lastPeek.Y) {
	  continue;
	}
	else {
	  lastPeek = out.back();
	  out.pop_back();					
	}
      }
      
      while(!out.empty() && !rightTurn(out.back(), lastPeek, *it)) {
	lastPeek = out.back();
	out.pop_back();
      }
      out.push_back(lastPeek);
      lastPeek = *it;
    }
    // Fix rightmost point as it should be handled differently:
    out.push_back(lastPeek);
    if(out.back() == right) {
      out.pop_back();
    }
    return out;
  }

  ConvexHull(const Polygon &scatteredPoints) {
    const int numPoints = scatteredPoints.size();
    Polygon copy(scatteredPoints);
    // Sort input by x (lex):
    std::sort(copy.begin(), copy.end());

    // Find left and rightmost points:
    Point leftMost = copy[0];
    Point rightMost = copy[numPoints-1];

    //Split points in upper and lower:
    Polygon upperPoints;
    Polygon lowerPoints;
    for(Polygon::const_iterator it = copy.begin(); it != copy.end(); ++it) {
      Point p = *it;
      if(colinear(leftMost, rightMost, p)) {
	continue;
      }
      if(leftTurn(leftMost, rightMost, p)) {
	upperPoints.push_back(p);
      }
      else { // right turn:
	lowerPoints.push_back(flipY(p));
      }
    }
    //cerr << "Leftmost: " << leftMost << ", rightmost: " << rightMost << endl;
    //cerr << "Upper points: " << upperPoints << endl;
    //cerr << "Lower points: " << lowerPoints << endl;
    
    upperPoints = upperHull(leftMost, rightMost, upperPoints);    
    lowerPoints = upperHull(flipY(leftMost), flipY(rightMost), lowerPoints);

    //cerr << "Upper hull: " << upperPoints << endl;
    //cerr << "Lower hull: " << lowerPoints << endl;
    
    //Make points of hull:
    size = upperPoints.size() + lowerPoints.size();
    points = new Point[size+1];
    int i = 0;
    for(Polygon::const_iterator it = upperPoints.begin(); it != upperPoints.end(); ++it) {
      points[i++] = *it;
    }
    points[i++] = rightMost;
    for(Polygon::const_reverse_iterator it = lowerPoints.rbegin(); it != lowerPoints.rend(); ++it) {
      points[i++] = flipY(*it);
    }
  }
};
std::ostream& operator<<(std::ostream& os, const ConvexHull &obj) {
  os << "{ ";
  for(int i = 0; i < obj.size; ++i) {
    os << obj.points[i] << " ";
  }
  os << "}";
  return os;
}

// Returns true if the lines intersect. 
// If the lines intersect, the intersection point may be stored in i.
bool getLineIntersection(Point p0, Point p1, Point p2, Point p3, Point2D &i) {
  if(p0 == p2 || p0 == p3 || p1 == p2 || p1 == p3 || overlap(Line(p0,p1),Line(p2,p3)))
    return false;

  Point s1, s2;
  s1.X = p1.X - p0.X;     
  s1.Y = p1.Y - p0.Y;
  s2.X = p3.X - p2.X;     
  s2.Y = p3.Y - p2.Y;
  
  long det = -s2.X * s1.Y + s1.X * s2.Y;
  if(det == 0) {
    //std::cerr << "det 0";
    return false;
  }
  double t = ( s2.X * (p0.Y - p2.Y) - s2.Y * (p0.X - p2.X)) / (double)det;
  if(t < 0 || t > 1)
    return false;
  
  i = Point2D(p0.X + (t * s1.X), p0.Y + (t * s1.Y));
  if(i.X > p3.X || i.X < p2.X || epsEq(i,p0) || epsEq(i,p1) || epsEq(i,p2) || epsEq(i,p3))
    return false;
  return true;
}
bool getLineIntersection(Line l1, Line l2, Point2D &i) {
  return getLineIntersection(l1.P1, l1.P2, l2.P1, l2.P2, i);
}
double getY(const Line &l, double x) {
  if(epsEq(x, l.P1.X))
    return l.P1.Y;
  if(epsEq(x, l.P2.X))
    return l.P2.Y;
  return l.P1.Y + ((l.P2.Y-l.P1.Y)/(double)(l.P2.X-l.P1.X))*(x-l.P1.X);
}

struct EventPoint {
  double x;
  int type, idx;
  Line l1, l2;
  EventPoint() {}
  EventPoint(const EventPoint &e) : x(e.x), type(e.type), idx(e.idx), l1(e.l1), l2(e.l2) {}
  EventPoint(double x, int type, int idx, const Line &l) : x(x), type(type), idx(idx), l1(l) {}
  EventPoint(double x, int type, int idx, const Line &l1, const Line &l2) : x(x), type(type), idx(idx), l1(l1), l2(l2) {}
  bool operator<(const EventPoint &other) const {
    if(x != other.x)
      return x < other.x;
    if(type != other.type)
      return type < other.type;
    return idx < other.idx;
  }
};

void die(std::string s) {
  std::cerr << s << std::endl;
  int *a = NULL;
  a[4] = 34;
}

double trapezoidArea(const Line &above, const Line &below, double leftX, double rightX) {
  double a = getY(above, leftX)-getY(below, leftX);
  double b = getY(above, rightX)-getY(below, rightX);
  //std::cerr << "Area " << leftX << "<x<" << rightX << ", below=" << below << ", above=" << above << ": " << (rightX-leftX) * (a+b)/2 << std::endl;
  return (rightX-leftX) * (a+b)/2;
}

void checkForCrossEvent(const SweepLine &s, int i1, int i2, EventQueue &q, int &idx, double x) {
  if(i1 < 0 || i1 >= (int)s.size() || i2 < 0 || i2 >= (int)s.size())
    return; // out of range.
  Point2D crossPoint;
  if(getLineIntersection(s[i1], s[i2], crossPoint) && crossPoint.X+1e-6 >= x) {
    //std::cerr << "Adding cross event points at x=" << crossPoint.X << " for line " << s[i1] << " and " << s[i2] << std::endl;
    q.insert(EventPoint(crossPoint.X, CROSS, ++idx, s[i1], s[i2]));
  }
}

// Assume lines point right.
double polygonArea(const LineVector &lines) {
  double x = 1e9;
  SweepLine s; // Notice: General implementation should use a set here!  
  int qIdx = 0;
  
  EventQueue q;
  // Insert all non-vertical segments into q:
  for(LineVector::const_iterator it = lines.begin(); it != lines.end(); ++it) {
    const Line &l = *it;
    if(l.P1.X == l.P2.X)
      continue;
    if(l.P1.X < x)
      x = l.P1.X;
    //std::cerr << "Adding event points of for line " << l.P1.X << "," << l.P1.Y << "->" << l.P2.X << "," << l.P2.Y << std::endl;
    q.insert(EventPoint(l.P1.X, START, ++qIdx, l));
    q.insert(EventPoint(l.P2.X, END, ++qIdx, l));
  }

  double area = 0;
    
  // Handle all event points at x. Update area when progressing x.
  while(!q.empty()) {
    EventPoint e = *q.begin(); q.erase(q.begin()); // Find and remove first event.
    /*
    std::cerr << "Sweep line when handling event point of type " << e.type << " at x=" << e.x << std::endl;
    for(unsigned int i = 0; i < s.size(); ++i)
      std::cerr << " " << s[i] << std::endl;//*/

    if(e.x > x+1e-6) {
      // Update area:
      if(s.size()%2 != 0) {
	die("Size not multiple of 2!"); // TODO! This check fails in judge!
      }
      for(unsigned int i = 1; i < s.size(); i += 2) {
	Line &above = s[i];
	Line &below = s[i-1];
	area += trapezoidArea(above, below, x, e.x);
      }      
    }
    x = e.x;
    int attentionAt = -1;
    // Handle event point.
    switch(e.type) {
    case START:
      for(unsigned int i = 0; i < s.size(); ++i) {
	if(getY(s[i], x+1e-4) > getY(e.l1, x+1e-4)) {
	  s.insert(s.begin()+i, e.l1);
	  attentionAt = i;
	  break;
	}
      }
      if(attentionAt == -1) {
	attentionAt = (int)s.size();
	s.push_back(e.l1);
      }
	
      // Check around attentionAt!
      checkForCrossEvent(s, attentionAt-1, attentionAt, q, qIdx, x);
      checkForCrossEvent(s, attentionAt, attentionAt+1, q, qIdx, x);

      break;
    case END:
      for(unsigned int i = 0; i < s.size(); ++i) {
	if(e.l1 == s[i]) {
	  s.erase(s.begin()+i);
	  checkForCrossEvent(s, i-1, i, q, qIdx, x);
	  break;
	}
      }
      break;
    case CROSS:
      for(unsigned int i = 0; i < s.size(); ++i) {
	if(e.l1 == s[i]) {
	  if(i > 0 && e.l2 == s[i-1]) {
	    /* ALREADY SWAPPED!
	    std::swap(s[i], s[i-1]);
	    checkForCrossEvent(s, i-2, i-1, q, qIdx, x);
	    checkForCrossEvent(s, i, i+1, q, qIdx, x);*/
	  }
	  else if(i+1 < s.size() && e.l2 == s[i+1]) {
	    std::swap(s[i], s[i+1]);
	    checkForCrossEvent(s, i-1, i, q, qIdx, x);
	    checkForCrossEvent(s, i+1, i+2, q, qIdx, x);
	  }
	  else {
	    die("Lines not adjacent in sweep line for cross!");
	  }
	  break;
	}
      }
      break;
    }
  }

  //std::cerr << "Computed area of polygon with " << lines.size() << " lines: " << area << std::endl;
  return area;
}

int loadPolygon(std::vector<Point> &v) {
  int n;
  Point pt;
  std::cin >> n;
  for(int i = 0; i < n; ++i) {
    std::cin >> pt.X >> pt.Y;
    v.push_back(pt);
  }
  return n;
}

void addToLineVector(const std::vector<Point> &pts, LineVector &lines) {
  for(unsigned int i = 0; i < pts.size(); ++i) {
    Point p1 = pts[i];
    Point p2 = pts[(i+1)%pts.size()];
    if(p1.X > p2.X)
      std::swap(p1, p2);
    lines.push_back(Line(p1, p2));
  }
}

double getArea(const ConvexHull &ch) {
  int res = 0;
  Point prev = ch.points[ch.size-1];
  for(int i = 0; i < ch.size; ++i) {
    Point &p = ch.points[i];
    res += prev.X*p.Y - prev.Y*p.X;
    //cerr << "Area + " << prev << p << ": " << (prev.X*p.Y - prev.Y*p.X) << endl;
    prev = p;
  }
  return -0.5*res;
}

// TODO: Create more stable CH algorithm.
int main() {  
  for(int cas = 1; true; ++cas) {
    Polygon v1;
    int n = loadPolygon(v1);
    if(n == 0)
      return 0;
    printf("Tile #%d\n", cas);

    LineVector a;
    addToLineVector(v1, a);
    double areaA = polygonArea(a);

    ConvexHull ch(v1);
    //cerr << "CH: " << ch << endl;
    double areaB = getArea(ch);

    //cerr << "Area A (polygon): " << areaA << ", B (convex hull):" << areaB << endl;

    // output: 
    printf("Wasted Space = %.2lf %%\n\n", 100.00*(areaB-areaA)/areaB);
  }
}
