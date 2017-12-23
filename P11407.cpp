int main() {
  int ret[100001];
  FORI(100001)
    ret[i] = i; // 1^2 + 1^2 + ...
  for(int i = 2; i*i <= 10000; ++i) {
    for(int n = i*i; n <= 10000; ++n) {
      // Try to improve ret[n] using i^2:
      if(ret[n-i*i]+1 < ret[n])
	ret[n] = ret[n-i*i]+1;
    }
  }
  FORCAS {
    GI(N);
    cout << ret[N] << endl;
  }
}
