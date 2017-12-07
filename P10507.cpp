int main() {
  int N, M;
  string s;
  bool active[26], newActive[26];
  bool a[26][26];
  
  while(cin >> N) {
    cin >> M >> s;

    // Reset:
    FORI(26) {
      active[i] = newActive[i] = false;
      FORJ(26) {
	a[i][j] = false;
      }
    }

    // Init:
    FORI(3)
      active[s[i]-'A'] = true;
    FORI(M) {
      cin >> s;
      int from = s[0]-'A', to = s[1]-'A';
      a[from][to] = a[to][from] = true;
    }
    
    int numActive = 3;
    int time = 0;
    bool improved = true;
    while(improved && numActive < N) {
      ++time;
      //cerr << "Time " << time << " num active: " << numActive << endl;
      improved = false;
      FORI(26) { // Try to wake up i:
	if(active[i]) {
	  continue; // Already woke
	}
	int cnt = 0;
	FORJ(26) {
	  if(!active[j] || !a[i][j])
	    continue;
	  ++cnt;
	  if(cnt == 3) {
	    newActive[i] = true;
	    ++numActive;
	    improved = true;
	    break;
	  }
	} // FORJ
      } // FORI
      FORI(26)
	active[i] = active[i] || newActive[i];
    } // while improved

    if(numActive == N)
      cout << "WAKE UP IN, " << time << ", YEARS" << endl;
    else
      cout << "THIS BRAIN NEVER WAKES UP" << endl;
  }
  return 0;
}
