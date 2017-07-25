int main() {
  FORCAS {
    vector<string> v;
    int N; cin >> N;
    string s;
    FORI(N) {
      cin >> s;
      v.push_back(s);
    }
    sort(v.begin(), v.end());
    bool ok = true;
    FORI(N-1) {
      if(v[i].size() > v[i+1].size())
	continue;
      bool allSame = true;
      FORUJ(v[i].size()) {
	if(v[i][j] != v[i+1][j]) {
	  allSame = false;
	  break;
	}
      }
      if(allSame) {
	ok = false;
	break;
      }
    }
    if(ok)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}
