char lca(const char a, const char b, int const * const parents, bool * const marked) {
  if(a == 'R' || b == 'R')
    return 'R'; // Rome is always LCA of rome,anything!
  char aa = a;
  while(aa != 'R') {
    marked[aa-'A'] = true;
    aa = (char)(parents[aa-'A']+'A');
  }
  marked['R'-'A'] = true;

  char ret = b;
  while(!marked[ret-'A'])
    ret = (char)(parents[ret-'A']+'A');

  aa = a;
  while(aa != 'R') {
    marked[aa-'A'] = false;
    aa = (char)(parents[aa-'A']+'A');
  }
  marked['R'-'A'] = false;  
  
  return ret;
}

int main() {
  string s1, s2;
  int parents[26];
  bool marked[26];
  memset(marked, false, 26*sizeof(bool));
  FORCAS {
    if(cas != 0)
      cout << endl;
    int m, q; // |roads|, |queries|
    cin >> m >> q;
    FORI(m) {
      cin >> s1 >> s2;
      parents[s2[0]-'A'] = s1[0]-'A';
    }
    FORI(q) {
      cin >> s1 >> s2;
      char a = s1[0];
      char b = s2[0];
      char L = lca(a, b, parents, marked);
      while(a != L) {
	cout << a;
	a = (char)(parents[a-'A']+'A');
      }
      cout << L;
      stack<char> st;
      while(b != L) {
	st.push(b);
	b = (char)(parents[b-'A']+'A');	
      }
      while(!st.empty()) {
	cout << st.top();
	st.pop();
      }
      cout << endl;
    }
  }
  return 0;
}
