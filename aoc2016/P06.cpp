int cnt[8][26];

int main() {
  FORI(8) {
    FORJ(26) {
      cnt[i][j] = 0;
    }
  }
  string s;
  while(cin >> s) {
    FORUI(s.size()) {
      cnt[i][s[i]-'a']++;
    }
  } // while cin >> s
  FORI(8) {
    char best;
    int bestCnt = 99999;
    FORJ(26) {
      if(cnt[i][j] < bestCnt && cnt[i][j] > 0) {
	bestCnt = cnt[i][j];
	best = (char)(j+'a');
      }
    }
    cout << best;
  }
  cout << endl;
}
