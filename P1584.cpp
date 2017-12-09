int main() {
  FORCAS {
    GS(s); 
    int len = (int)s.size();
    s = s + s;
    string best = s;
    for(int i = 1; i < len; ++i) {
      string y(&s[i]);
      if(y < best)
	best = y;
    }
    FORI(len)
      cout << best[i];
    cout << endl;
  }
  return 0;
}
