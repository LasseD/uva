int main() {
  string s;
  char mar[6] = {'M','A','R','G','I','T'};
  int cmar[6] = { 1 , 3 , 2 , 1 , 1 , 1 };
  
  int cnt[26];
  FORCAS {
    memset(cnt, 0, sizeof(cnt));
    cin >> s;
    FORUI(s.size())
      ++cnt[s[i]-'A'];
    int min = 100000;
    FORI(6) {
      int m = cnt[mar[i]-'A'] / cmar[i];
      if(m < min)
	min = m;
    }
    cout << min << endl;
  }
  return 0;
}
