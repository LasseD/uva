int main() {
  int a1, a2, b1, b2, c1, c2;
  while(true) {
    cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;
    if(0 == (a1 | b1 | c1 | a2 | b2 | c2))
      return 0;
    // Compute intersection:
    // https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
    double a = -a1/(double)b1;
    double c = c1/(double)b1;
    double b = -a2/(double)b2;
    double d = c2/(double)b2;

    if(b1 == 0) {
      if(a1 == 0)
	die(); // Not a valid formula
      // a1*x = c1 => x == c1/a1
      double xx = c1/(double)a1;
      if(b2 == 0) { // parallel
	if(a2 == 0)
	  die(); // Not a valid formula
	printf("No fixed point exists.\n");
	continue;
      }
      printf("The fixed point is at %.2lf %.2lf.\n", xx, b*xx+d);
      continue;
    }
    if(b2 == 0) {
      if(a2 == 0)
	die(); // Not a valid formula
      double xx = c2/(double)a2;
      printf("The fixed point is at %.2lf %.2lf.\n", xx, a*xx+c);
      continue;
    }

    if(ABS(a-b) < 1e-8) { // Parallel
      printf("No fixed point exists.\n");
      continue;
    }

    double x = (d-c)/(a-b);
    double y = a*x+c;
    printf("The fixed point is at %.2lf %.2lf.\n", x, y);
  }
}
