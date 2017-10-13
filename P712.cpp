int main() {
  int n, m, x[8];
  string leafs, s, xs[8];
  for(int cas = 1; true; ++cas) {
    cin >> n;
    if(n == 0)
      return 0;
    cout << "S-Tree #" << cas << ":" << endl;
    FORI(n) {
      cin >> xs[i];
      x[i] = xs[i][1]-'1';
    }    
    cin >> leafs;
    cin >> m;
    FORI(m) {
      cin >> s;
      int idx = 0;
      FORJ(n) { // For each level
	int variable = x[j];
	int value = s[variable]-'0';
	idx += value*(1 << (n-j-1));
      }
      cout << leafs[idx];
    }    
    cout << endl << endl;
  }
}
