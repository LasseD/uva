int main() {
  int N;
  while(true) {
    cin >> N;
    if(N == 0)
      return 0;
    int *a = new int[N];
    FORI(N)
      cin >> a[i];
    sort(a, a+N);
    
    int prev = 0;
    bool ok = true;
    FORI(N) {
      if(a[i] > prev + 200)
	ok = false;
      prev = a[i];
    }
    if(1422-prev > 100)
      ok = false;
    if(ok)
      cout << "POSSIBLE" << endl;
    else
      cout << "IMPOSSIBLE" << endl;

    delete []a;
  }
}
