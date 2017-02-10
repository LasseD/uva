typedef pair<Point2D,double> Circle;
#define CENTER first
#define RADIUS second

bool colinear(const Point &A, const Point &B, const Point &C) {
  return (B.XX-A.XX)*(C.YY-A.YY) - (B.YY-A.YY)*(C.XX-A.XX) == 0;
}
double dist(const Point2D &p, const Point &q) {
  double dx = p.XX-(double)q.XX;
  double dy = p.YY-(double)q.YY;
  return sqrt(dx*dx + dy*dy);
}
double dist(const Point &p, const Point &q) {
  return dist(Point2D(p.XX,p.YY), q);
}

// http://stackoverflow.com/questions/4103405/what-is-the-algorithm-for-finding-the-center-of-a-circle-from-three-points
Circle buildFrom3(Point A, Point B, Point C) {
  if(colinear(A, B, C))
    die();
  if(A.XX == B.XX)
    swap(B, C); // now A.XX != B.XX, because not co-linear.
  if(B.XX == C.XX) {
    swap(A, B); // Now B.XX != C.XX and A.XX != B.XX
  }
  if(B.YY == A.YY) {
    swap(A, C); // Now aSlope will not be 0.
  }
  if(B.XX == A.XX)
    die();
  if(B.XX == C.XX)
    die();
  if(B.YY == A.YY)
    die();

  double yDelta_a = B.YY - A.YY;
  double xDelta_a = B.XX - A.XX;
  double yDelta_b = C.YY - B.YY;
  double xDelta_b = C.XX - B.XX;
  
  Point2D center;
  
  double aSlope = yDelta_a/xDelta_a;
  double bSlope = yDelta_b/xDelta_b;
  center.XX = (aSlope*bSlope*(A.YY - C.YY) + bSlope*(A.XX + B.XX)
	       - aSlope*(B.XX+C.XX) )/(2.0* (bSlope-aSlope) );
  center.YY = -1.0*(center.XX - (A.XX+B.XX)/2.0)/aSlope + (A.YY+B.YY)/2.0;
  
  return Circle(center, dist(center, A));
}

Circle buildFrom2(const Point &p, const Point &q) {
  Point2D center((p.XX+q.XX)/2.0, (p.YY+q.YY)/2.0);
  return Circle(center, dist(center, p));
}

Circle buildEnclosingCircle(vector<Point> &Q) {
  if(Q.size() == 1) {
    Point2D center(Q[0].XX, Q[0].YY);
    return Circle(center, 0);
  }
  if(Q.size() == 2) {
    return buildFrom2(Q[0], Q[1]);
  }
  if(Q.size() == 3) {
    if(colinear(Q[0], Q[1], Q[2])) {
      if(dist(Q[0],Q[1]) > dist(Q[1],Q[2])) {
	if(dist(Q[0],Q[1]) > dist(Q[0],Q[2]))
	  return buildFrom2(Q[0], Q[1]);
	else
	  return buildFrom2(Q[0], Q[2]);
      }
      else {
	if(dist(Q[2],Q[1]) > dist(Q[0],Q[2]))
	  return buildFrom2(Q[2], Q[1]);
	else
	  return buildFrom2(Q[0], Q[2]);
      }
    }

    return buildFrom3(Q[0], Q[1], Q[2]);
  }
  return Circle(Point2D(0,0),0);
}

bool inCircle(const Circle &c, const Point &p) {
  return dist(c.CENTER, p) <= c.RADIUS + 1e-9;
}

/*
Processes points of S in a random order. Maintaining set P of processed points and the smallest circle c that encloses the union of P and Q. At each step, it tests whether the next point r to be processed belongs to c; if not, the algorithm replaces c by the result of a recursive call on (P,Q+r).
 */
Circle EmoWelzlSmallestEnclosure(vector<Point> &S, vector<Point> &Q) {
  Circle c = buildEnclosingCircle(Q);

  if(Q.size() == 3)
    return c;
  vector<Point> P;
  FORIT(vector<Point>, S) {
    Point r = *it;
    if(!inCircle(c, r)) {
      vector<Point> Q2(Q);
      Q2.push_back(r);
      c = EmoWelzlSmallestEnclosure(P, Q2);
    }
    P.push_back(r);
  }
  return c;
}

int main() {
  int N;
  while(true) {
    cin >> N;
    if(N == 0)
      return 0;
    vector<Point> poly;
    FORI(N) {
      Point p;
      cin >> p.XX >> p.YY;
      poly.push_back(p);
    }
    std::srand(std::time(0));
    random_shuffle(poly.begin(), poly.end());
    double R; cin >> R;

    vector<Point> Q;
    Circle c = EmoWelzlSmallestEnclosure(poly, Q);
    
    /*cerr << "Center: " << c.CENTER.XX << ", " << c.CENTER.YY << ", R=" << R << ", poly r=" << c.RADIUS << endl;//*/
    //printf("%.8lf\n", c.RADIUS);

    if(R >= c.RADIUS)
      cout << "The polygon can be packed in the circle." << endl;
    else
      cout << "There is no way of packing that polygon." << endl;//*/
  }
}	
