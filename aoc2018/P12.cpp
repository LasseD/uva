// RM "initial state: " from input
#define SIZE 1000
#define HALF_SIZE SIZE/2

bool v[SIZE], w[SIZE];
typedef map<string,bool> MAP;
MAP m;

int main() {
  FORI(SIZE)
    v[i] = w[i] = false;
  
  string s, ignore; char c;
  cin >> s;
  FORUI(s.size()) {
    if(s[i] == '#') {
      v[HALF_SIZE+i] = true;
    }
  }
  while(cin >> s >> ignore >> c) {
    m[s] = c == '#';
  }

  // Simulate:
  LL addX = 0;
  map<string,PI> m2; // encoding, PI(k, mi)

  LL GENS = 50000000000; // 20 for part 1
  //LL GENS = 200; // Use for testing
  for(LL k = 0; k < GENS; k++) {
    int mi = 9999999, ma = -9999999;
    FORI(SIZE)
      w[i] = false;
    FORI(SIZE-5) {
      stringstream ss;
      FORK(5)
	ss << (v[i+k] ? '#' : '.');
      if(m[ss.str()]) {
	w[i+2] = '#';
	mi = min(mi, i+2);
	ma = max(ma, i+2);
      }
    }
    swap(v,w);
    //cout << "After " << k << ": range " << mi << " -> " << ma << " range size " << (ma-mi+1) << endl;
    stringstream ss;
    for(int i = mi; i <= ma; i++) {
      ss << (v[i] ? '#' : '.');
    }
    s = ss.str();
    if(m2.find(s) == m2.end()) {
      m2[s] = PI(k, mi);
    }
    else {
      LL lastK = m2[s].first;
      LL lastMi = m2[s].second;
      cout << "Duplicate found! " << s << endl;
      cout << "generation now: " << k << ", then: " << lastK << endl;
      cout << "Starts at now: " << mi << ", then: " << lastMi << endl;
      addX = GENS-k-1;
      break;
    }//*/
  }
  
  LL answer1 = 0;    
  FORI(SIZE) {
    if(v[i])
      answer1+=i+addX-HALF_SIZE;
  }
  cout << answer1 << endl;
}
