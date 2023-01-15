typedef pair<PC,int> PCCI;

map<PC,char> m;
map<PCCI,ULL> cache; // XY,iterations -> cnt letter.

ULL go2(PC pc, char c, int rounds) {
  if(rounds == 0)
    return 0;
  PCCI pcci(pc,rounds);
  if(cache.find(pcci) != cache.end()) {
    return cache[pcci];
  }
  ULL ret = 0;
  char mid = m[pc];
  if(mid == c)
    ret++;
  ret += go2(PC(pc.first,mid), c, rounds-1);
  ret += go2(PC(mid,pc.second), c, rounds-1);

  cache[pcci] = ret;
  return ret;
}

ULL go(string s, char c, int rounds) {
  ULL ret = 0;
  FORUI(s.size()) {
    if(s[i] == c)
      ret++;
  }
  FORUI(s.size()-1) {
    PC pc(s[i],s[i+1]);
    ret += go2(pc, c, rounds);
  }
  
  return ret;
}

int main() {
  GS(t); // Template
  string s, ignore; char c;
  while(cin >> s >> ignore >> c) {
    m[PC(s[0], s[1])] = c;
  }

  // Simulate:
  ULL ma = 0, mi = 99999999999999;
  for(c = 'A'; c <= 'Z'; c++) {
    cache.clear();
    ULL cnt = go(t, c, 40); // 10 for part 1, 40 for part 2
    if(cnt == 0)
      continue;
    ma = max(ma, cnt);
    mi = min(mi, cnt);
  }

  /* Part 1:
  s = t; cout << s << endl;
  FORK(10) {
    stringstream ss;
    for(int i = 0; i < (int)s.size()-1; i++) {
      char c1 = s[i], c2 = s[i+1];
      ss << c1 << m[PC(c1,c2)];
    }
    ss << s[s.size()-1];
    s = ss.str();
    //cout << s << endl;
  }
  // Part 1:
  int cnt[26]; FORI(26) cnt[i] = 0;
  FORUI(s.size()) {
    cnt[s[i]-'A']++;
  }
  FORI(26) {
    if(cnt[i] == 0)
      continue;
    ma = max(ma, cnt[i]);
    mi = min(mi, cnt[i]);
  }
  */
  cout << "Most common: " << ma << endl;
  cout << "Least common: " << mi << endl;
  cout << (ma-mi) << endl;
}
