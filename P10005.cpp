typedef vector<Point> Polygon;
typedef pair<Point,Point> Line;

ostream& operator<<(ostream& os, const Point &obj) {
  os << "(" << obj.first << "," << obj.second << ")";
  return os;
}
ostream& operator<<(ostream& os, const Polygon &obj) {
  os << "[ ";
  for(Polygon::const_iterator it = obj.begin(); it != obj.end(); ++it) {
    os << *it << " ";
  }
  os << "]";
  return os;
}

/*
 * Convex hull represented bYY a list of points in clockwise order.
 */
bool rightTurn(const Point &lineStart, const Point &lineEnd, const Point &p) {
  return (lineEnd.XX-lineStart.XX)*(p.YY-lineStart.YY) - (lineEnd.YY-lineStart.YY)*(p.XX-lineStart.XX) < 0;
}
bool leftTurn(const Point &lineStart, const Point &lineEnd, const Point &p) {
  return (lineEnd.XX-lineStart.XX)*(p.YY-lineStart.YY) - (lineEnd.YY-lineStart.YY)*(p.XX-lineStart.XX) > 0;
}
bool colinear(const Point &lineStart, const Point &lineEnd, const Point &p) {
  return (lineEnd.XX-lineStart.XX)*(p.YY-lineStart.YY) - (lineEnd.YY-lineStart.YY)*(p.XX-lineStart.XX) == 0;
}
Point flipY(const Point &b) {
  return Point(b.XX, -b.YY);
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
      if(it->XX == lastPeek.XX) {
	if(it->YY < lastPeek.YY) {
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
    sort(&copy[0], &copy[numPoints]);

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

  Point2D getCenterMass() {
    long sumX = 0;
    long sumY = 0;
    long area = 0;
    FORUI(points.size()) {
      Point &p0 = points[i];
      Point &p1 = points[i+1];

      long triangleArea = (p0.XX * p1.YY) - (p1.XX * p0.YY);

      sumX += (p0.XX + p1.XX) * triangleArea;
      sumY += (p0.YY + p1.YY) * triangleArea;
      area += triangleArea;
    }
    return Point2D(sumX / 6.0 / area, sumY / 6.0 / area);
  }
};
ostream& operator<<(ostream& os, const ConvexHull &obj) {
  os << "{ ";
  for(int i = 0; i < obj.size; ++i) {
    os << obj.points[i] << " ";
  }
  os << "}";
  return os;
}

int main() {
  int N;
  while(true) {
    cin >> N;
    if(N == 0)
      return 0;
    Polygon poly;
    FORI(N) {
      Point p;
      cin >> p.XX >> p.YY;
      poly.push_back(p);
    }
    double R; cin >> R;

    if(N == 1) {
      cout << "The polygon can be packed in the circle." << endl;
      continue;
    }
    if(N == 2) {
      double dx = poly[0].XX-ch.poly[1].XX;
      double dy = poly[0].YY-ch.poly[1].YY;
      if(2*R >= sqrt(dx*dx+dy*dy))
	cout << "The polygon can be packed in the circle." << endl;
      else
	cout << "There is no way of packing that polygon." << endl;
      continue;
    }

    // Compute CH:
    ConvexHull ch(poly);

    Point2D centerMass = ch.getCenterMass();
    double dx = centerMass.XX-ch.points[0].XX;
    double dy = centerMass.YY-ch.points[0].YY;
    if(R >= sqrt(dx*dx+dy*dy))
      cout << "The polygon can be packed in the circle." << endl;
    else
      cout << "There is no way of packing that polygon." << endl;

    delete[] ch.points;
  }
}	
