#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>

// Geometry:
typedef std::pair<int,int> Point;
typedef std::pair<double,double> Point2D;
typedef std::pair<Point,Point> Line;
typedef std::vector<Line> LineVector;
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

void loadPolygon(std::vector<Point> &v) {
  int n;
  Point pt;
  std::cin >> n;
  for(int i = 0; i < n; ++i) {
    std::cin >> pt.X >> pt.Y;
    v.push_back(pt);
  }
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

// https://uva.onlinejudge.org/external/1/137.html
// Compute XOR area (area bonded by one polygon)
int main() {  
  while(true) {
    std::vector<Point> v1, v2;
    loadPolygon(v1);
    if(v1.size() == 0) {
      printf("\n");
      return 0;
    }
    loadPolygon(v2);
    LineVector ab;
    addToLineVector(v1, ab);
    addToLineVector(v2, ab);
    double areaAB = polygonArea(ab);
    // output: 
    printf("%8.2f", areaAB);
  }
}

/*
Old code:
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <limits.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <sstream>

typedef std::pair<double,double> Point;
typedef std::vector<Point> Polygon;
typedef std::pair<Point,Point> Line;
#define x first
#define y second
struct RefLine;
struct sweep_line_cmp;
typedef std::set<RefLine,sweep_line_cmp> slt;

bool rightTurn(double diffX, double diffY, double x1, double y1, const Point &p) {
  return diffX*(p.y-y1) < diffY*(p.x-x1);
}
bool rightTurn(const Point &p1, const Point &p2, const Point &p) {
  return rightTurn(p2.x-p1.x, p2.y-p1.y, p2.x, p2.y, p);
}
bool coLinear(double diffX, double diffY, double x1, double y1, const Point &p) {
  return std::abs(diffX*(p.y-(double)y1) - diffY*(p.x-(double)x1)) < 0.0001;
}
bool coLinear(const Point &p1, const Point &p2, const Point &p) {
  return coLinear(p2.x-p1.x, p2.y-p1.y, p2.x, p2.y, p);
}
bool rightTurn(const Point &prev, const Point &p, const Point &pl, const Point &pr) {
  if(!rightTurn(prev,p,pr)) {
    return false;
  }
  return rightTurn(p,pl,pr);
}

struct RefLine{
public:
  Line line;
  Polygon *ref;
  int i;
  const Point p1() const {
    return line.first;
  }
  const Point p2() const {
    return line.second;
  }  
  double y(Point p) const {
    if(p1().x == p2().x)
      return p.y;
    if(p.x == p1().x)
      return p1().y;
    if(p.x == p2().x)
      return p2().y;
    double a = (p2().y-p1().y) / (p2().x-p1().x);
    return p1().y + a*(p.x-p1().x);
  }
private:
  const Point pp1() const {
    return (*ref)[i];
  }
  const Point pp2() const {
    return (*ref)[(i+1)%ref->size()];
  }
  const Point left() const {
    Point p1 = pp1();
    Point p2 = pp2();
    if(p1.x < p2.x)
      return p1;
    if(p1.x > p2.x)
      return p2;
    if(p1.y < p2.y)
      return p1;
    return p2;
  }
  const Point right() const {
    Point p1 = pp1();
    Point p2 = pp2();
    if(p1.x < p2.x)
      return p2;
    if(p1.x > p2.x)
      return p1;
    if(p1.y < p2.y)
      return p2;
    return p1;
  }
public:
  RefLine() {}
  RefLine(Polygon *p, int i) : ref(p), i(i) {
    line = Line(left(),right());
  }  
  bool intersects(RefLine &r) {
    if(p1() == r.p1() || p1() == r.p2() || p2() == r.p1() || p2() == r.p2()) {
      if(p1() == r.p1() && coLinear(p1(), p2(), r.p2())) {
    //std::cerr << "case z " << std::endl;
    return true;
      }
      return false;
    }
    if(coLinear(p1(),p2(),r.p1()) || coLinear(p1(),p2(),r.p2())) {
      return rightTurn(r.p1(),r.p2(),p1()) != rightTurn(r.p1(),r.p2(),p2());
    }
    if(coLinear(r.p1(),r.p2(),p1()) || coLinear(r.p1(),r.p2(),p2())) {
      return rightTurn(p1(),p2(),r.p1()) != rightTurn(p1(),p2(),r.p2());
    }
    return (rightTurn(  p1(),  p2(),r.p1()) != rightTurn(  p1(),  p2(),r.p2())) && 
           (rightTurn(r.p1(),r.p2(),  p1()) != rightTurn(r.p1(),r.p2(),  p2()));
  }
};
std::ostream& operator<<(std::ostream& out, const RefLine& e){
  return out << e.p1().x << "," << e.p1().y << "->" << e.p2().x << "," << e.p2().y;
}

struct EventPoint {
  RefLine ref;
  Point point;
  EventPoint(const RefLine &rl, const Point &p) : ref(rl), point(p) {}

  bool isStartEvent() const {
    return point.x == ref.p1().x && point.y == ref.p1().y;
  }

  /*
    First by event point.
    Then by event type: end < cross < start
    then by ref.
   * /
  bool operator< (const EventPoint& o) const {
    if(point != o.point)
      return point < o.point;
    if(isStartEvent() != o.isStartEvent()) {
      return !isStartEvent();      
    }
    // both same type. Order by ref:
    if(ref.p1() != o.ref.p1())
      return ref.p1() < o.ref.p1();
    return ref.p2() < o.ref.p2();
  }
};
std::ostream& operator<<(std::ostream& out, const EventPoint& e){
  return out << e.point.x << ',' << e.point.y << " on " << e.ref;
}

struct Intersection {
  RefLine refA;
  RefLine refB;
  Point intersection;

  Intersection() {}

  Intersection(const RefLine &refA, const RefLine &refB) : refA(refA), refB(refB) {
    double p0_x = refA.p1().x;
    double p0_y = refA.p1().y;
    double p1_x = refA.p2().x;
    double p1_y = refA.p2().y;
    double p2_x = refB.p1().x;
    double p2_y = refB.p1().y;
    double p3_x = refB.p2().x;
    double p3_y = refB.p2().y;

    double s10_x = p1_x - p0_x;
    double s10_y = p1_y - p0_y;
    double s32_x = p3_x - p2_x;
    double s32_y = p3_y - p2_y;

    double s02_x = p0_x - p2_x;
    double s02_y = p0_y - p2_y;
    double t_numer = s32_x * s02_y - s32_y * s02_x;
    double denom = s10_x * s32_y - s32_x * s10_y;

    double t;
    if(denom == 0) { // co-linear!
      if(!(refA.p1() == refB.p1())) {
        throw std::exception();
      }
      if(s10_x == s32_x) {
    if(s10_y < s32_y)
      intersection = refA.p2();
    else
      intersection = refB.p2();
      }
      else if(s10_x < s32_x)
    intersection = refA.p2();
      else
    intersection = refB.p2();
    }
    else {
      t = t_numer / denom;
      intersection = Point(p0_x + (t * s10_x),p0_y + (t * s10_y));
    }

    if(intersection == refA.p1() || intersection == refA.p2()) {
      this->refA.i = -1;
    }
    if(intersection == refB.p1() || intersection == refB.p2()) {
      this->refB.i = -1;
    }
  }
};
std::ostream& operator<<(std::ostream& out, const Intersection& i){
   return out << i.intersection.x << ',' << i.intersection.y;
}

Point p;
struct sweep_line_cmp {
  bool operator() (const RefLine &a, const RefLine &b) const {
    // check y at p.x.
    double ay = a.y(p);
    double by = b.y(p);
    if(ay != by) {
      return ay < by;
    }
    // CHECK START/END CONNECTIONS:
    if(a.p2() == b.p1())
      return true;
    if(b.p2() == a.p1())
      return false;
    // Check vertical:
    if(a.p1().x == a.p2().x) {
      if(b.p1().x == b.p2().x)
    return a.p1().y == b.p1().y ? a.p2().y < b.p2().y : a.p1().y < b.p2().y;
      if(a.p2() == b.p2())
    return true;
      if(a.p1() == b.p1())
    return false;
      return false;
    }
    else if(b.p1().x == b.p2().x) {
      if(a.p2() == b.p2())
    return false;
      if(a.p1() == b.p1())
    return true;
      return true;
    }
    // Since lines intersect at p and they are not start/end combination, check at x+1 (unless at least one ends)
    Point newX(p.x+1,p.y);
    if(a.p2().x == p.x || b.p2().x == p.x) {
      newX.x = p.x-1;
    }
    ay = a.y(newX);
    by = b.y(newX);
    if(ay != by)
      return ay < by;
    return a.p2() < b.p2();
  }
};

void print_sweep_line(const slt &sweep_line) {
  //std::cerr << "Sweep line at " << p.x << "," << p.y << std::endl;
  for(slt::const_iterator it = sweep_line.begin(); it != sweep_line.end(); ++it) {
    //std::cerr << " " << *it << std::endl;
  }
  //std::cerr << std::endl;
}

std::string polyString(const Polygon &b) {
  std::stringstream ss;
  for(Polygon::const_iterator it = b.begin(); it != b.end(); ++it) {
    ss << " " << it->x << "," << it->y;
  }   
  return ss.str(); 
}

bool intersects(slt::iterator &line, Intersection &i) {
  RefLine ra = *line;
  ++line;
  RefLine rb = *line;
  if(ra.intersects(rb)) {
    i = Intersection(ra,rb);
    //std::cerr << "Intersection found: " << i << " of " << ra << "x" << rb << std::endl;
    return true;
  }
  return false;
}

bool compute_first_intersection(const std::vector<RefLine> &s, Intersection &intersection) {
  // Build event queue:
  std::set<EventPoint> events;
  for(std::vector<RefLine>::const_iterator it = s.begin(); it != s.end(); ++it) {
    EventPoint e1(*it, it->p1());
    EventPoint e2(*it, it->p2());
    if(it->p1() == it->p2())
      continue;
    if(events.find(e1) != events.end()) {
      events.erase(e1);
      events.erase(e2);
    }
    else {
      events.insert(e1);
      events.insert(e2);
    }
  }
  
  // Sweep:
  slt sweep_line;
  for(std::set<EventPoint>::const_iterator it = events.begin(); it != events.end(); ++it) {
    EventPoint event = *it;

    if(!event.isStartEvent()) { // end event!
      //std::cerr << "Handling end event: " << event << std::endl;
      slt::iterator it3 = sweep_line.find(event.ref);
      if(it3 == sweep_line.end()) {
    //std::cerr << "event not in sl! " << event << std::endl;
    throw std::exception();
      }
      if(it3 != sweep_line.begin()) {
    --it3;
    RefLine prev = *it3;
    ++it3;
    sweep_line.erase(it3);
    it3 = sweep_line.find(prev);
    ++it3;
    if(it3 != sweep_line.end()) {
      --it3;
            if(intersects(it3, intersection))
         return true;
    }
      }
      else {
    sweep_line.erase(it3);
      }
      p = event.point;
        print_sweep_line(sweep_line);
    }
    else {
      //std::cerr << "Handling start event: " << event << std::endl;
      p = event.point;
      std::pair<slt::iterator,bool> ires = sweep_line.insert(event.ref);
      // compute intersections
      slt::iterator it2 = ires.first;
      if(it2 != sweep_line.begin()) {
    --it2;
    if(intersects(it2, intersection))
       return true;
      }
      ++it2;
      if(it2 != sweep_line.end()) {
    --it2;
    if(intersects(it2, intersection))
       return true;
      }
        print_sweep_line(sweep_line);
    }
  }

  return false;
}

bool compute_first_intersection(Polygon &a, Polygon &b, Intersection &intersection) {
  std::vector<RefLine> s;
  for(unsigned int i = 0; i < a.size(); ++i) {
    RefLine r(&a, i);
    s.push_back(r);
  }
  for(unsigned int i = 0; i < b.size(); ++i) {
    RefLine r(&b, i);
    s.push_back(r);
  }
  return compute_first_intersection(s, intersection);
}

void augment(Polygon &a, const int i, const Point &p) {
  Polygon out;
  int ii = 0;
  for(Polygon::const_iterator it = a.begin(); it != a.end(); ++it) {
    out.push_back(*it);
    if(ii == i)
      out.push_back(p);    
    ++ii;
  }
  a = out;
}

void computeAllIntersections(const Polygon &a, const Polygon &b, std::set<std::pair<int,int> > &intersections) {
  //std::cerr << "Intersections: " << std::endl;
  std::map<Point,int> fromA;
  int i = 0;
  for(Polygon::const_iterator it = a.begin(); it != a.end(); ++it) {
    fromA.insert(std::make_pair(*it, i));
    ++i;
  }
  i = 0;
  for(Polygon::const_iterator it = b.begin(); it != b.end(); ++it) {
    Point p = *it;
    std::map<Point,int>::iterator it2 = fromA.find(p);
    if(it2 != fromA.end()) {
      // find adjacent points:
      Point aPrev = a[(it2->second-1+a.size())%a.size()];
      Point aNext = a[(it2->second+1+a.size())%a.size()];
      Point bPrev = b[(i-1+b.size())%b.size()];
      Point bNext = b[(i+1+b.size())%b.size()];
      if(!((aPrev == bPrev && aNext == bNext) || (aPrev == bNext && aNext == bPrev))) {
    // not same prev and next points.
    // now it depends on whether points are co-linear and perform right turns...
    bool res;
    if(aPrev == bNext || aNext == bPrev) {
      res = false;
    }
    else if(aPrev == bPrev || aNext == bNext) {
      res = true;
    }
    else if(coLinear(aPrev,p,aNext)) {
      res = rightTurn(aPrev,p,bPrev) != rightTurn(aPrev,p,bNext);
    }
    else if(rightTurn(aPrev,p,aNext)) {
      res = (rightTurn(aPrev,p,bPrev) && rightTurn(p,aNext,bPrev)) ||
            (rightTurn(aPrev,p,bNext) && rightTurn(p,aNext,bNext));
    }
    else {
      res = (!rightTurn(aPrev,p,bPrev) && !rightTurn(p,aNext,bPrev)) ||
            (!rightTurn(aPrev,p,bNext) && !rightTurn(p,aNext,bNext));
    }

    if(res) {
          intersections.insert(std::make_pair(it2->second, i));
      //std::cerr << " " << a[it2->second].x << " " << a[it2->second].y << std::endl;
    }
      }
    }
    ++i;
  }
}

double getPolygonArea(const Polygon &a) {
  if(a.size() < 3)
    return 0;
  double res = 0;
  Point prev = a.back();
  for(Polygon::const_iterator it = a.begin(); it != a.end(); ++it) {
    Point p = *it;
    res += (prev.x*p.y - prev.y*p.x);
    prev = p;
  }
  return res/-2;
}

Polygon readPolygon(int size) {
  Polygon b;
  int x, y;
  //std::cerr << ",";
  for(int i = 0; i < size; ++i) {
    std::cin >> x >> y;
    Point p(x,y);
    if(!b.empty() && p == b.back())
      continue;
    b.push_back(p);
  }

  // Check if degenerate:
  if(b.size() < 3) {
    b.clear();
    return b;
  }
  double area = getPolygonArea(b);
  if(std::abs(area) < 0.0001) {
    b.clear();
  }
  return b;
}

std::pair<double,double> getInterval(Polygon &a, double x) {
  double min = a[0].y;
  double max = a[0].y;
  Point p(x,0);
  for(unsigned int i = 0; i < a.size(); ++i) {
    RefLine r(&a, i);
    if(r.p1().x <= x && r.p2().x >= x) {
      if(r.p1().x == r.p2().x) {
        min = std::min(min,r.p1().y);
        max = std::max(max,r.p2().y);
      }
      min = std::min(min,r.y(p));
      max = std::max(max,r.y(p));
    }
  }
  return std::make_pair(min,max);
}

Point computeCentroid(const Polygon &vertices) {
  Point centroid(0,0);
  double signedArea = 0.0;
  double x0 = 0.0; // Current vertex X
  double y0 = 0.0; // Current vertex Y
  double x1 = 0.0; // Next vertex X
  double y1 = 0.0; // Next vertex Y
  double a = 0.0;  // Partial signed area

  // For all vertices except last
  unsigned int i=0;
  for(; i<vertices.size()-1; ++i) {
    x0 = vertices[i].x;
    y0 = vertices[i].y;
    x1 = vertices[i+1].x;
    y1 = vertices[i+1].y;
    a = x0*y1 - x1*y0;
    signedArea += a;
    centroid.x += (x0 + x1)*a;
    centroid.y += (y0 + y1)*a;
  }

  // Do last vertex
  x0 = vertices[i].x;
  y0 = vertices[i].y;
  x1 = vertices[0].x;
  y1 = vertices[0].y;
  a = x0*y1 - x1*y0;
  signedArea += a;
  centroid.x += (x0 + x1)*a;
  centroid.y += (y0 + y1)*a;
  
  signedArea *= 0.5;
  centroid.x /= (6.0*signedArea);
  centroid.y /= (6.0*signedArea);
  
  return centroid;
}

bool contains(Polygon &a, const Polygon &b) {
  if(a.size() < 3 || b.size() < 3)
    return false;
  Point pb = computeCentroid(b);
  std::pair<double,double> pair = getInterval(a, pb.x);
  return pair.first <= pb.y && pb.y <= pair.second;
}

Polygon getIntersectionPolygon(const Polygon &a, const Polygon &b, const std::set<std::pair<int,int> > &intersections) {  
  const std::pair<int,int> leftmost_intersection_indices = *(intersections.begin());

  std::map<int,int> aToB, bToA;
  //std::cerr << "intersections of a and b: " << std::endl;
  for(std::set<std::pair<int,int> >::const_iterator it = intersections.begin(); it != intersections.end(); ++it) {
    //std::cerr << " " << it->x << "," << it->y << " (";
    //std::cerr << a[it->x].x << "," << a[it->x].y << " = ";
    //std::cerr << b[it->y].x << "," << b[it->y].y << ")" << std::endl;
    aToB.insert(*it);
    bToA.insert(std::make_pair(it->second,it->first));
  }

  //std::cerr << "Start walking for c: " << std::endl;
  Polygon c;
  Point initPrev = a[(leftmost_intersection_indices.x-1+a.size())%a.size()];
  Point init = a[leftmost_intersection_indices.first];
  Point initA = a[(leftmost_intersection_indices.x+1+a.size())%a.size()];
  Point initB = b[(leftmost_intersection_indices.y+1+b.size())%b.size()];
  bool followingA = rightTurn(initPrev,init,initB,initA);
  int abI = followingA ? leftmost_intersection_indices.first : leftmost_intersection_indices.second;
  while(true) {
    if(followingA) {
      //std::cerr << " " << a[abI].x << " " << a[abI].y << " from a at " << abI << std::endl;
      Point prev = a[abI];
      c.push_back(prev);
      abI = (abI+1)%a.size();
      if(abI == leftmost_intersection_indices.first)
    break;
      std::map<int,int>::iterator it = aToB.find(abI);
      if(it != aToB.end()) { // new intersection found, walk rightmost:
    Point p = a[abI];
    Point pa = a[(abI+1)%a.size()];
    Point pb = b[(it->second+1)%b.size()];
    if(rightTurn(prev,p,pa,pb)) {
      followingA = false;
      abI = it->second;
    }
      }
    }
    else {
      //std::cerr << " " << b[abI].x << " " << b[abI].y << " from b at " << abI << std::endl;
      Point prev = b[abI];
      c.push_back(prev);
      abI = (abI+1)%b.size();
      if(abI == leftmost_intersection_indices.second)
    break;
      std::map<int,int>::iterator it = bToA.find(abI);
      if(it != bToA.end()) { // new intersection found:
    Point p = b[abI];
    Point pb = b[(abI+1)%b.size()];
    Point pa = a[(it->second+1)%a.size()];
    if(rightTurn(prev,p,pb,pa)) {
      followingA = true;
      abI = it->second;
    }
      }
    }
  }
  //std::cerr << std::endl;
  return c;
}

int main() {
  while(true) {
    // Read polygons a and b:
    int sa, sb;
    std::cin >> sa;
    if(sa == 0) {
      printf("\n");
      return 0;
    }
    Polygon a = readPolygon(sa);
    std::cin >> sb;
    Polygon b = readPolygon(sb);

    // Compute intersections:
    // Augment intersections onto original polys:
    Intersection ii;
    while(compute_first_intersection(a,b,ii)) {
      RefLine refA = ii.refA;
      RefLine refB = ii.refB;
      if(refA.ref != &a) {
    std::swap(refA,refB);
      }
      augment(a,refA.i,ii.intersection);
      augment(b,refB.i,ii.intersection);
    }

    // Find all intersections:
    std::set<std::pair<int,int> > intersections;
    computeAllIntersections(a, b, intersections);
    
    //std::cerr << "polygon a: " << polyString(a) << std::endl;
    //std::cerr << "Area a " << getPolygonArea(a) << std::endl;
    //std::cerr << "polygon b: " << polyString(b) << std::endl;
    //std::cerr << "Area b " << getPolygonArea(b) << std::endl;

    // compute intersection polygon:
    if(intersections.empty() || a.size() < 3 || b.size() < 3) { // either not intersecting, same, or inside one another!
      double sizeA = getPolygonArea(a);
      double sizeB = getPolygonArea(b);
      if(contains(a,b) || contains(b,a)) {
        printf("%8.2f", std::abs(sizeA-sizeB));
      }
      else {
        printf("%8.2f", std::abs(sizeA+sizeB));
      }
      continue;
    }

    Polygon c = getIntersectionPolygon(a,b,intersections);

    //std::cerr << "Intersection polygon: " << std::endl;
    //std::cerr << "Area c " << getPolygonArea(c) << std::endl;

    double aa = getPolygonArea(a);
    double bb = getPolygonArea(b);
    double cc = getPolygonArea(c);
    double res = aa+bb-2*cc;
    printf("%8.2f", res);
  }
}
 */
