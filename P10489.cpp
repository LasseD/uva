int main() {
  FORCAS {
    GI(N); GI(B);
    int rem = 0;
    FORI(B) {
      GI(K);
      int x = 1;
      FORJ(K) {
	GI(a);
	x*=a;
	x%=N;
      }
      rem += x;
      rem %= N;
    }
    cout << rem << endl;
  }
  return 0;
}
