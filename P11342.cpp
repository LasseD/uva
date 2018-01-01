typedef pair<PI,PI> PPI;

int main() {
  PPI ret[50001];
  FORI(50001)
    ret[i].YY.YY = 0; // unset.

  for(int x = 0; x*x <= 50000; ++x) {
    long xx = x*x;
    for(int y = x; xx+y*y <= 50000; ++y) {
      long yy = y*y, xxyy = xx+yy;
      for(int z = y; xxyy+z*z <= 50000; ++z) {
	long zz = z*z, xxyyzz = xxyy+zz;
	if(ret[xxyyzz].YY.YY != -1)
	  ret[xxyyzz] = PPI(PI(x,y),PI(z,-1));
      }
    }
  }
  // GOGOGO!
  FORCAS {
    GI(N);
    if(ret[N].YY.YY == -1) {
      cout << ret[N].XX.XX << " " << ret[N].XX.YY << " " << ret[N].YY.XX << endl;
    }
    else {
      cout << -1 << endl;
    }
  }
  return 0;
}
