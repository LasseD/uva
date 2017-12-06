int main() {
  string a[10];
  
  FORCAS {
    cout << "Case " << cas+1 << ":" << endl;
    GI(n);
    FORI(n) {
      cin >> a[i];
    }
    FORI(n) {
      string &s = a[i];
      FORJ(n) {
	if(s[j] != '.')
	  continue;
	// Try all letters:
	for(char c = 'A'; true; ++c) {
	  if(j > 0 && s[j-1] == c)
	    continue;
	  if(j < n-1 && s[j+1] == c)
	    continue;
	  if(i > 0 && a[i-1][j] == c)
	    continue;
	  if(i < n-1 && a[i+1][j] == c)
	    continue;
	  s[j] = c;
	  break;
	} // for char
      } // FORJ
      cout << s << endl;
    }
  }
  return 0;
}
