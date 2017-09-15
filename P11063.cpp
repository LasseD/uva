int main() {
  int n;
  bool b[20001];
  int a[100];
  for(int cas = 1; cin >> n; ++cas) {
    cout << "Case #" << cas << ": It is ";

    bool ok = true;
    memset(b, false, sizeof(b));
    FORI(n) {
      cin >> a[i];
      if(a[i] < 1 || (i > 0 && a[i] <= a[i-1]))
	ok = false;
    }
    FORI(n) {
      for(int j = i; j < n; ++j) {
	int sum = a[i]+a[j];
	if(b[sum]) {
	  ok = false;
	  //cerr << "Collision on " << sum << endl;
	  break;
	}
	b[sum] = true;
      }
      if(!ok)
	break;
    }

    if(!ok)
      cout << "not ";
    
    cout << "a B2-Sequence." << endl << endl;
  }
  return 0;
}
