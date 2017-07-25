PD operator+(const PD &a, const PD &b) {
  return PD(a.XX+b.XX, a.YY+b.YY);
}
PD operator-(const PD &a, const PD &b) {
  return PD(a.XX-b.XX, a.YY-b.YY);
}
PD operator*(const PD &p, const double &t) {
  return PD(t*p.XX, t*p.YY);
}

double distSquared(PD a, PD b) {
  double dx = a.XX-b.XX;
  double dy = a.YY-b.YY;
  return dx*dx + dy*dy;
}

double dist(PD a, PD b) {
  return sqrt(distSquared(a, b));
}

double epsEq(double a, double b) {
  return ABS(a-b) < 1e-9;
}
double epsEq(PD a, PD b) {
  return epsEq(a.XX, b.XX) && epsEq(a.YY, b.YY);
}

double clamp01(double a) {
  if(a < 0)
    return 0;
  if(a > 1)
    return 1;
  return a;
}

double dotProduct(PD a, PD b) {
  return a.XX*b.XX + a.YY*b.YY;
}

// Stolen from: http://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
// Return minimum distance point on line segment vw minimizing the distance to point p
PD nearestPointOnLineSegment(PD v, PD w, PD p) {
  if(epsEq(v, w))
    return v; // v == w case. Avoid division by zero.
  double l2 = distSquared(v, w);
  // Consider the line extending the segment, parameterized as v + t (w - v).
  // We find projection of point p onto the line. 
  // It falls where t = [(p-v) . (w-v)] / |w-v|^2
  // We clamp t from [0,1] to handle points outside the segment vw.
  PD wv = w-v;
  double t = clamp01(dotProduct(p-v, wv) / l2);
  PD projection = v + (wv * t); // Projection falls on the segment
  return projection;
}

int main() {
  PD m, prev, p, best, cur;
  while(cin >> m.XX >> m.YY) {
    int N; cin >> N;
    cin >> prev.XX >> prev.YY;
    best = prev;
    FORI(N) {
      cin >> p.XX >> p.YY;
      cur = nearestPointOnLineSegment(prev, p, m);
      if(distSquared(m, cur) < distSquared(m, best))
	best = cur;
      prev = p;
    }
    printf("%.4lf\n%.4lf\n", best.XX, best.YY);
  }
  return 0;
}
