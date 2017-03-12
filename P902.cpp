/*
26 characters => 5 bit.
 */

string tos(int N, ULL best) {
  char cc[11];
  FORI(N) {
    cc[N-i-1] = (char)('a'+(best & 31));
    best >>= 5;
  }
  cc[N] = '\0';
  return string(cc);
}

int main() {
  string s; 
  int N;
  while(cin >> N >> s) {
    if(N > (int)s.size())
      die(); // Not possible. Doesn't make sense.
    map<ULL,int> m;
    ULL curr = 0;
    ULL mask = 0;
    FORI(N) {
      curr = (curr << 5) + (s[i]-'a');
      mask = (mask << 5) + 31; // Fill with 1's.
    }
    m.insert(make_pair(curr, 1));
    ULL best = curr;
    int bestCnt = 1;
    //cerr << "Init: " << tos(N, curr) << ": " << curr << endl;
      
    for(int i = N; i < (int)s.size(); ++i) {
      curr = mask & ((curr << 5) + (s[i]-'a'));
      //cerr << " " << i << ": " << tos(N, curr) << ": " << curr << endl;
      map<ULL,int>::iterator it = m.find(curr);
      if(it == m.end()) {
	m.insert(make_pair(curr, 1));
      }
      else {
	++it->second;
	if(it->second > bestCnt) {
	  bestCnt = it->second;
	  best = curr;
	}
      }
    }
    cout << tos(N, best) << endl;
  }
  return 0;
}
