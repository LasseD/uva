int main() {
  FORCAS {
    int N; cin >> N;
    string s; cin >> s;
    int ret = 0;
    FORI(N) {
      if(s[i] != '.')
	continue;
      ++ret;
      if(i+1 < N)
	s[i+1] = '#';
      if(i+2 < N)
	s[i+2] = '#';
    }
    cout << "Case " << (cas+1) << ": " << ret << endl;
  }
  return 0;
}
