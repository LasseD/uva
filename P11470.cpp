int main() {
  int sums[5], a;
  for(int cas = 1; true; ++cas) {
    int N; cin >> N; 
    if(N == 0) 
      return 0;
    int half = (N+1)/2;
    FORI(half)
      sums[i] = 0;
    // top sums:
    FORY(half) {
      FORX(y) {
	cin >> a;
	sums[x] += a; // outer boxes
      }
      FORX((N-2*y)) {
	cin >> a;
	sums[y] += a;
      }
      FORX(y) {
	cin >> a;
	sums[y-1-x] += a; // outer boxes
      }      
    }
    for(int y = N-half-1; y >= 0; --y) {
      FORX(y) {
	cin >> a;
	sums[x] += a; // outer boxes
      }
      FORX((N-2*y)) {
	cin >> a;
	sums[y] += a;
      }
      FORX(y) {
	cin >> a;
	sums[y-1-x] += a; // outer boxes
      }      
    }
    cout << "Case " << cas << ":";
    FORI(half)
      cout << " " << sums[i];
    cout << endl;
  }
}
