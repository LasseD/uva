int main() {
  int cnt[26];
  FORCAS {
    GI(R); GI(C);
    vector<string> v(R);
    FORI(R)
      cin >> v[i];
    int ret = 0;    
    FORX(C) {
      cnt['A'-'A'] = cnt['C'-'A'] = cnt['G'-'A'] = cnt['T'-'A'] = 0;
      FORY(R) {
	cnt[v[y][x]-'A']++;
      }
      char best = 'A';
      if(cnt['C'-'A'] > cnt[best-'A'])
	best = 'C';
      if(cnt['G'-'A'] > cnt[best-'A'])
	best = 'G';
      if(cnt['T'-'A'] > cnt[best-'A'])
	best = 'T';

      cout << best;
      ret += R - cnt[best-'A'];
    }
    cout << endl << ret << endl;
  }
  return 0;
} // int main
