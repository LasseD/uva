int main() {
  int k, m;
  string s;
  while(true) {
    cin >> k; if(k == 0) return 0;
    cin >> m;
    set<string> freddy;
    FORI(k) {
      cin >> s;
      freddy.insert(s);
    }
    bool ok = true;
    FORI(m) {
      int c, r; cin >> c >> r;
      int inFreddy = 0;
      FORJ(c) {
	cin >> s;
	if(freddy.find(s) != freddy.end())
	  ++inFreddy;
      }
      if(inFreddy < r)
	ok = false;
    }
    if(ok)
      cout << "yes" << endl;
    else
      cout << "no" << endl;
  }
}
