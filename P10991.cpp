double angleA(double a, double b, double c) {
  return acos((b*b+c*c-a*a)/(2.0*b*c));
}

double area(double a, double b, double c) {
  double s = (a+b+c)/2.0; // Semiperimeter
  return sqrt(s*(s-a)*(s-b)*(s-c));
}

int main() {
  FORCAS {
    double r1, r2, r3;
    cin >> r1 >> r2 >> r3;
    double a1 = M_PI*r1*r1;
    double a2 = M_PI*r2*r2;
    double a3 = M_PI*r3*r3;
    double triangleArea = area(r1+r2, r2+r3, r3+r1);
    double angle1 = angleA(r2+r3, r1+r2, r1+r3);
    double angle2 = angleA(r3+r1, r1+r2, r2+r3);
    double angle3 = angleA(r2+r1, r3+r2, r1+r3);
    printf("%.6lf\n", triangleArea - a1*angle1/(2*M_PI) - a2*angle2/(2*M_PI) - a3*angle3/(2*M_PI));
  }
  return 0;
}
