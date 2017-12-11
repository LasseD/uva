int main() {
  int cnt[26];
  FORCAS {
    GI(N);
    memset(cnt, 0, sizeof(cnt));
    if(N > 0) {
      GS(s);
      FORI(N) {
	char c = s[i];
	cnt[c-'A']++;
      }
    }
    else
      die();
    cout << "Case " << cas+1 << ": ";
    if(cnt['A'-'A'] == N)
      cout << "ABANDONED";
    else if(N == cnt[0]+cnt['B'-'A'])
      cout << "BANGLAWASH";
    else if(N == cnt[0]+cnt['W'-'A'])
      cout << "WHITEWASH";
    else if(cnt['W'-'A']==cnt['B'-'A'])
      cout << "DRAW " << cnt['B'-'A'] << " " << cnt['T'-'A'];
    else if(cnt['W'-'A']>cnt['B'-'A'])
      cout << "WWW " << cnt['W'-'A'] << " - " << cnt['B'-'A'];
    else if(cnt['W'-'A']<cnt['B'-'A'])
      cout << "BANGLADESH " << cnt['B'-'A'] << " - " << cnt['W'-'A'];
    cout << endl;
  }
  return 0;
}
