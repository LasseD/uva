string anotb(const string &a, const string &b) {
  set<char> s;
  FORUI(b.size()) {
    char c = b[i];
    s.insert(c);
  }
  
  stringstream ss;
  FORUI(a.size()) {
    char c= a[i];
    if(s.find(c) == s.end()) {
      ss << c;
    }
  }
  return ss.str();
}
string aandb(const string &a, const string &b) {
  set<char> s;
  FORUI(b.size()) {
    char c = b[i];
    s.insert(c);
  }
  stringstream ss;
  FORUI(a.size()) {
    char c= a[i];
    if(s.find(c) != s.end()) {
      ss << c;
    }
  }
  return ss.str();
}

bool cmp(const string &a, const string &b) {
  if(a.size() != b.size())
    return a.size() < b.size();
  return a < b;
}

int main() {
  string line, s;
  int cnt[10], answer2 = 0;
  FORI(10)
    cnt[i] = 0;
  while(getline(cin, line)) {
    vector<string> v, q;
    stringstream ss; ss << line;
    FORI(10) {
      ss >> s;
      sort(&s[0], &s[s.size()]);
      v.push_back(s);
    }
    ss >> s; if(s != "|") die(); // assert |

    // 4 to guess:
    FORI(4) {
      ss >> s;
      sort(&s[0], &s[s.size()]);
      q.push_back(s);
      if(s.size() == 2)
	cnt[1]++;
      else if(s.size() == 3)
	cnt[7]++;
      else if(s.size() == 4)
	cnt[4]++;
      else if(s.size() == 7)
	cnt[8]++;
    }
    
    // Part 2 analysis:
    sort(v.begin(), v.end(), cmp);
    string s0;
    const string s069[3] = {v[6], v[7], v[8]};
    const string s1 = v[0];
    string s2;
    string s3;
    const string s235[3] = {v[3], v[4], v[5]};
    const string s4 = v[2];
    string s5;
    string s6;
    const string s7 = v[1];
    const string s8 = v[9];
    string s9;

    // Find some segments a-g:
    string bd = anotb(s4,s1);
    // Find d and s0:
    FORI(3) {
      s0 = s069[i];
      string d = anotb(bd, s0);
      if(d.size() == 1) {
	break; // Found s0
      }
    }
    // Find c, s9, and s6:
    FORI(3) {
      string x = s069[i];
      if(x == s0) {
	continue; // Not a match
      }
      string y = anotb(s1, x);
      if(y.size() == 1) {
	s6 = x;
      }
      else {
	s9 = x;
      }
    }
    // Find s2, s3, and s5:
    FORI(3) {
      string x = s235[i];
      string y = aandb(s1, x);
      string z = anotb(s6, x);
      if(y.size() == 2) {
	s3 = x;
      }
      else if(z.size() == 1) {
	s5 = x;
      }
      else {
	s2 = x;
      }
    }

    // Use map:
    map<string,int> m;
    m[s0] = 0;
    m[s1] = 1;
    m[s2] = 2;
    m[s3] = 3;
    m[s4] = 4;
    m[s5] = 5;
    m[s6] = 6;
    m[s7] = 7;
    m[s8] = 8;
    m[s9] = 9;
    int c4 = 0;
    FORIT(vector<string>, q) {
      c4 = 10*c4 + m[*it];
    }
    answer2 += c4;
  }
  cout << "Answer 1: " << (cnt[1]+cnt[8]+cnt[4]+cnt[7]) << endl;
  cout << "Answer 2: " << answer2 << endl;
}
