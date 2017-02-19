int main() {
  int N, x0, y0, z0, x1, y1, z1, w, x2, y2, z2, x3, y3, z3;
  while(true) {
    cin >> N;
    if(N == 0)
      return 0;
    cin >> x0 >> y0 >> z0 >> w;
    x1 = x0+w;
    y1 = y0+w;
    z1 = z0+w;

    // Read rest of cubes:
    FORI(N-1) {
      cin >> x2 >> y2 >> z2 >> w;
      x3 = x2+w;
      y3 = y2+w;
      z3 = z2+w;

      x0 = MAX(x0, x2);
      y0 = MAX(y0, y2);
      z0 = MAX(z0, z2);

      x1 = MIN(x1, x3);
      y1 = MIN(y1, y3);
      z1 = MIN(z1, z3);
    }

    if(x1 <= x0 || y1 <= y0 || z1 <= z0)
      cout << 0 << endl;
    else
      cout << (x1-x0)*(y1-y0)*(z1-z0) << endl;
  }
}
