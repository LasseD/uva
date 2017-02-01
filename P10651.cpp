typedef unsigned long UL;

UL masks[12];

void build(int marbles, int fromI, int rem, UL cur, map<UL,int> *m) {
  if(rem == 0) {
    // Move all right and left:
    int min = marbles;
    FORI(10) {
      if((cur & masks[i]) == masks[i] && (cur & masks[i+1]) == masks[i+1] && (cur & masks[i+2]) != masks[i+2]) {
	UL lower = (cur | masks[i+2]) ^ (masks[i+1] | masks[i]);
	int test = m[marbles-1][lower];
	//cerr << "For " << marbles << " marbles: " << cur << "<-" << lower << endl;
	min = MIN(test, min);
      }
      if((cur & masks[11-i]) == masks[11-i] && (cur & masks[10-i]) == masks[10-i] && (cur & masks[9-i]) != masks[9-i]) {
	UL lower = (cur | masks[9-i]) ^ (masks[10-i] | masks[11-i]);
	int test = m[marbles-1][lower];
	//cerr << "For " << marbles << " marbles: " << cur << "->" << lower << endl;
	min = MIN(test, min);
      }
    }
    //cerr << "For " << marbles << " marbles: " << cur << ": " << min << endl;
    m[marbles].insert(pair<UL,int>(cur, min));
    return;
  }
  for(int pos = fromI; pos < 12; ++pos) {
    build(marbles, pos+1, rem-1, cur | masks[pos], m);
  }
}

int main() {
  masks[0] = 1;
  for(int i = 1; i < 12; ++i) {
    masks[i] = masks[i-1] << 1;
  }

  map<UL,int> m[13];
  m[0].insert(pair<UL,int>(0,0));
  for(int marbles = 1; marbles <= 12; ++marbles) {
    build(marbles, 0, marbles, 0, m);
  }

  FORCAS {
    string s;
    cin >> s;
    UL L = 0;
    int cnt = 0;
    FORI(12) {
      if(s[i] == 'o') {
	++cnt;
      }
      L = (L << 1) + (s[i] == 'o');
    }
    cout << m[cnt][L] << endl;
  }
  return 0;
}
