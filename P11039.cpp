int main() {
  PI *a = new PI[500000];
  FORCAS {
    int N, x;
    cin >> N;
    FORI(N) {
      cin >> x;
      a[i].YY = x < 0;
      if(x < 0)
	x = -x;
      a[i].XX = x;
    }
    sort(a, a+N);
    int ret = 1;
    for(int i = 1; i < N; ++i) {
      if(a[i].YY != a[i-1].YY)
	++ret;
    }
    cout << ret << endl;
  }
  return 0;
}
