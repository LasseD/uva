#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <algorithm>

typedef std::pair<int,int> Point;
typedef std::vector<Point> Polygon;
typedef std::pair<Point,Point> Line;
#define xx first
#define yy second

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
    std::cout << actualNumPoints;
    for(i = 0; i < actualNumPoints; ++i)
      std::cout << " " << points[i].first << " " << points[i].second;
    std::cout << std::endl;
  }
};

void makeRandomPolygon() {
  int n = 3 + rand() % 100; // between 3 and 12 points

  Polygon poly;
  for(int i = 0; i < n; ++i) {
    int XX = rand() % 100;
    int YY = rand() % 100;
    poly.push_back(Point(XX, YY));
  }
  ConvexHull ch(poly);
}

int main () {
  /* initialize random seed: */
  srand(time(NULL));

  makeRandomPolygon();
  makeRandomPolygon();
  std::cout << 0 << std::endl;

  return 0;
}
