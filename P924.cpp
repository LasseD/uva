int main() {
  int N, E, F, T; // Number of employees
  vector<int> friends[2501];
  while(cin >> N) {
    FORI(N)
      friends[i].clear();
    FORI(N) {
      cin >> E;
      FORJ(E) {
	cin >> F;
	if(F != i)
	  friends[i].push_back(F);
      }
    }
    cin >> T; // Test cases:
    FORI(T) {
      cin >> E;
      if(friends[E].empty()) {
	cout << 0 << endl;
      }
      else {
	// Push waves:
	vector<int> v;
	set<int> seen;
	v.push_back(E);
	seen.insert(E);
	int wave = -1;
	int maxWaveSize = -1;
	int maxWave = -1;
	while(!v.empty()) {
	  ++wave;
	  if(wave > 0 && maxWaveSize < (int)v.size()) {
	    maxWaveSize = (int)v.size();
	    maxWave = wave;
	  }
	  // Handle wave:
	  vector<int> w;
	  FORIT(vector<int>, v) {
	    int e = *it;
	    FORIT2(vector<int>, friends[e]) {
	      int e2 = *it2;
	      if(seen.find(e2) != seen.end())
		continue; // already seen.
	      seen.insert(e2);
	      w.push_back(e2);
	    } // FORIT2
	  } // FORIT
	  v = w;
	} // while(!v.empty())
	cout << maxWaveSize << " " << maxWave << endl;
      } // else
    }
  }
  return 0;
}
