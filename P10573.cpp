int main() {
  string line;
  getline(cin, line);
  int cases, r1, r2;
  stringstream ss1; ss1 << line; ss1 >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    getline(cin, line);
    stringstream ss2; ss2 << line;
    if(!(ss2 >> r1 >> r2)) {
      int t = r1;
      // PI*(L*L-2*S*S) = PI*(t/2*t/2-2*t/4*t/4) = PI(tt/4-/8) = PI*tt/8
      printf("%.4lf\n", M_PI*t*t/8.0);
    }
    else {
      // PI* ... (r1+r2)^2-r1^2-r2^2 = r1^2+r2^2+2r1r2-r1^2-r2^2 = 2r1r2
      printf("%.4lf\n", M_PI*2.0*r1*r2);
    }
  }
  return 0;
}
