#include <iostream>
#include <vector>
#include <algorithm>

typedef std::pair<int,int> Point;
typedef std::vector<Point> Polygon;
typedef std::pair<Point,Point> Line;
#define xx first
#define yy second

std::ostream& operator<<(std::ostream& os, const Point &obj) {
  os << "(" << obj.first << "," << obj.second << ")";
  return os;
}
std::ostream& operator<<(std::ostream& os, const Polygon &obj) {
  os << "[ ";
  for(Polygon::const_iterator it = obj.begin(); it != obj.end(); ++it) {
    os << *it << " ";
  }
  os << "]";
  return os;
}

/*
 * Convex hull represented byy a list of points in clockwise order.
 */
bool rightTurn(const Point &lineStart, const Point &lineEnd, const Point &p) {
  return (lineEnd.xx-lineStart.xx)*(p.yy-lineStart.yy) - (lineEnd.yy-lineStart.yy)*(p.xx-lineStart.xx) < 0;
}
bool leftTurn(const Point &lineStart, const Point &lineEnd, const Point &p) {
  return (lineEnd.xx-lineStart.xx)*(p.yy-lineStart.yy) - (lineEnd.yy-lineStart.yy)*(p.xx-lineStart.xx) > 0;
}
bool colinear(const Point &lineStart, const Point &lineEnd, const Point &p) {
  return (lineEnd.xx-lineStart.xx)*(p.yy-lineStart.yy) - (lineEnd.yy-lineStart.yy)*(p.xx-lineStart.xx) == 0;
}
Point flipY(const Point &b) {
  return Point(b.xx, -b.yy);
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
      if(it->xx == lastPeek.xx) {
	if(it->yy < lastPeek.yy) {
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
    std::sort(&copy[0], &copy[numPoints]);

    // Find left and rightmost points:
    Point leftMost = copy[0];
    Point rightMost = copy[numPoints-1];

    //Split points in upper and lower:
    Polygon upperPoints;
    Polygon lowerPoints;
    for(int i = 1; i < numPoints-1; ++i) {			
      Point p = copy[i];
      if(colinear(leftMost, rightMost, p)) {
	continue;
      }
      if(leftTurn(leftMost, rightMost, p)) {
	upperPoints.push_back(p);
      }
      else {
	lowerPoints.push_back(flipY(p));
      }
    }

    upperPoints = upperHull(leftMost, rightMost, upperPoints);
    lowerPoints = upperHull(flipY(leftMost), flipY(rightMost), lowerPoints);
    
    //Make points of hull:
    int actualNumPoints = size = upperPoints.size() + lowerPoints.size();
    points = new Point[actualNumPoints];
    int i = 0;
    for(Polygon::const_iterator it = upperPoints.begin(); it != upperPoints.end(); ++it) {
      points[i++] = *it;
    }		
    points[i] = rightMost;
    i = actualNumPoints;
    for(Polygon::const_iterator it = lowerPoints.begin(); it != lowerPoints.end(); ++it) {
      i--;
      if(i != actualNumPoints-1)
	points[i+1] = flipY(*it);
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

int main() {
  char name[22];
  while(true) {
    // Read poly:
    std::cin >> name;
    if(name[0] == '#')
      return 0;
    std::cout << name;
    Point centerMass;
    std::cin >> centerMass.xx >> centerMass.yy;

    Polygon poly;
    while(true) {
      int XX, YY;
      std::cin >> XX >> YY;
      if(XX == 0 && YY == 0)
	break;
      poly.push_back(Point(XX, YY));
    }
    // Compute CH:
    ConvexHull ch(poly);

    // Candidate line segments:
    std::vector<Line> candidates;
    for(int i = 0; i < ch.size; ++i) {
      Point a = ch.points[i];
      Point b = ch.points[(i+1)%ch.size];
      Point oA(a.xx+(b.yy-a.yy), a.yy-(b.xx-a.xx));
      Point oB(b.xx+(b.yy-a.yy), b.yy-(b.xx-a.xx));
      if(rightTurn(oA, a, centerMass) && rightTurn(b, oB, centerMass)) {
	candidates.push_back(Line(a,b));
      }
    }

    // check all points:
    int *nums = new int[candidates.size()];
    for(int i = 0; i < candidates.size(); ++i)
      nums[i] = 0;
    for(unsigned int i = 0; i < poly.size(); ++i) {
      int num = i+1;
      Point p = poly[i];
      int j = 0;
      for(std::vector<Line>::const_iterator it = candidates.begin(); it != candidates.end(); ++it, ++j) {
	Line line = *it;
	if(colinear(line.first, line.second, p)) {
	  nums[j] = std::max(nums[j], num);
	}
      }
    }
    
    int best = poly.size();
    for(unsigned int i = 0; i < candidates.size(); ++i) {
      best = std::min(best, nums[i]);
    }

    std::cout << " " << best << std::endl;
    delete[] nums;
    delete[] ch.points;
  }
}	
