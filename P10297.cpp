#define EPS 1e-5

int main() {
  double D, V;
  while(true) {
    cin >> D >> V;
    if(D == 0 && V == 0)
      return 0;
    double R = D/2;
    double A = M_PI*R*R;
    double r = 3.0/4.0/M_PI*(D*A-V-M_PI*R*R*R*2.0/3.0);
    r = pow(r, 1.0/3.0);

    printf("%.3lf\n", 2*r);
  }
}
