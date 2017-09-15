int main() {
  int a, b, c;
  FORCAS {
    int N;
    cin >> N;
    N-=2;
    cin >> a >> b;
    int ret = a-b;
    int maxVal = MAX(a,b);
    FORI(N) {
      cin >> c;
      ret = MAX(ret, maxVal-c);
      maxVal = MAX(maxVal, c);      
    }
    cout << ret << endl;
  }
  return 0;
}
