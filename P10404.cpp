int main() {
  bool *ret = new bool[1000001]; 
  ret[0] = false;
  int n, m, a[10];
  while(cin >> n >> m) {
    FORI(m)
      cin >> a[i];
    sort(a, a+m);

    for(int i = 1; i <= n; ++i) {
      bool any = false;
      FORJ(m) {
	if(i-a[j] < 0)
	  break;
	if(!ret[i-a[j]]) {
	  any = true;
	  break;
	}	
      }
      ret[i] = any;
      //cerr << "(" << i << ":" << (ret[i]?'S':'O') << ")";
    }
    if(ret[n])
      cout << "Stan wins" << endl;
    else
      cout << "Ollie wins" << endl;
  }
  return 0;
}
