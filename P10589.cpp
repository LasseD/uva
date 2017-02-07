double dist(double x1, double y1, double x2, double y2) {
  double dx = x1-x2;
  double dy = y1-y2;
  return sqrt(dx*dx+dy*dy);
}

bool inside(double x, double y, double a) {
  return dist(x, y, 0, 0) <= a &&
    dist(x, y, a, 0) <= a &&
    dist(x, y, 0, a) <= a &&
    dist(x, y, a, a) <= a;
}

int main() {
  int N;
  long long a;
  double x, y;
  while(true) {
    cin >> N; // Points
    if(N == 0)
      return 0;
    cin >> a; // Side length
    int M = 0;
    FORI(N) {
      cin >> x >> y;
      if(inside(x, y, a)) {
	++M;
      }
    }
    double area = M*a*a/(double)N;
    printf("%.5lf\n", area);
  }
}
