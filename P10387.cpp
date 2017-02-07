int main() {
  int a, b, s, m, n;
  while(true) {
    cin >>a>>b>>s>>m>>n;
    if(a+b+s+m+n == 0)
      return 0;
    // a=width, b=height, s=time, m=bounce left/right, n=bounce up/down.
    double distX = m*a;
    double distY = n*b;
    double angle = atan2(distY, distX)*180.0/M_PI;
    double speed = sqrt(distX*distX+distY*distY)/(double)s;
    printf("%.2lf %.2lf\n", angle, speed);
  }
}
