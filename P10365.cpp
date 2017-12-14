int main() {
  int ret[1001];
  ret[0] = 0;
  for(int i = 1; i <= 1000; ++i)
    ret[i] = 2+4*i;

  for(int W = 1; W <= 1000; ++W) {
    for(int L = W; L*W <= 1000; ++L) {
      int area = W*L;
      for(int H = L; H*area <= 1000; ++H) {
	int volume = area*H;
	int surface = 2*(area + L*H + W*H);
	if(ret[volume] > surface)
	  ret[volume] = surface;
      }
    }
  }
  
  FORCAS {
    GI(N);
    cout << ret[N] << endl;
  }
  return 0;
}
