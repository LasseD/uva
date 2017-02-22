/*
1 = c/X + c/Y
X = sqrt(x*x-w*w)
Y = sqrt(y*y-w*w)
 */
int main() {
  double x, y, c;
  while(cin >> x >> y >> c) {
    double minW = 0;
    double maxW = x;
    while(maxW-minW > 0.000001) {
      double w = (minW+maxW)/2.0;
      double X = sqrt(x*x-w*w);
      double Y = sqrt(y*y-w*w);
      double one = c/X + c/Y;
      if(one < 1.0)
	minW = w;
      else
	maxW = w;
    }
    printf("%.3lf\n", (minW+maxW)/2.0);
  }
  return 0;
}
