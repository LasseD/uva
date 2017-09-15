int main() {
  LL KN[51][51]; // k, n
  LL n, k, m;
  while(cin >> n >> k >> m) {
    // k == 1:
    for(int nn = 1; nn <= n; ++nn) {
      KN[1][nn] = nn <= m ? 1 : 0;
    }
    for(int kk = 2; kk <= k; ++kk) {
      for(int nn = 1; nn <= n; ++nn) {	
	KN[kk][nn] = 0;
	for(int lastBar = 1; lastBar <= m && nn-lastBar >= 1; ++lastBar) {
	  KN[kk][nn] += KN[kk-1][nn-lastBar];
	}
      }
    }
    cout << KN[k][n] << endl;
  }
  return 0;
}
