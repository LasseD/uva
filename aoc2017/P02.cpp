int main() {
  string s;
  LL answer1 = 0, answer2 = 0;
  while(getline(cin, s)) {
    stringstream ss; ss << s;
    LL x, mi = 9999999999, ma = -99999999;
    vector<LL> v;
    while(ss >> x) {
      ma = max(ma, x);
      mi = min(mi, x);
      v.push_back(x);
    }
    int added = 0;
    FORUI(v.size()) {
      FORUJ(v.size()) {
	if(i != j) {
	  if(v[i] % v[j] == 0) {
	    answer2 += v[i]/v[j];
	    added++;
	  }
	}
      }
    }
    if(added != 1) {
      cerr << "ERROR: " << added << " on a line!" << endl;
    }
    answer1 += ma-mi;
  }
  cout << answer1 << endl;
  cout << answer2 << endl;
}
