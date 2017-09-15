bool cmp(const PI &a, const PI &b) {
  if(a.P1 != b.P1)
    return a.P1 < b.P1;
  bool aOdd = 1 == (1 & a.P2);
  bool bOdd = 1 == (1 & b.P2);
  if(aOdd != bOdd)
    return aOdd;
  if(aOdd)
    return a.P2 > b.P2;
  return a.P2 < b.P2;
}

int main() {
  int N, M, x;
  PI a[100000];

  while(true) {
    cin >> N >> M;
    cout << N << " " << M << endl;
    if(N == 0 && M == 0)
      return 0;
    FORI(N) {
      cin >> x;
      a[i] = PI(x%M, x);
    }
    sort(a, a+N, cmp);
    FORI(N)
      cout << a[i].second << endl;
  }
}
