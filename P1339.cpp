int main() {
  string s1, s2;
  char c1[26], c2[26];
  
  while(cin >> s1 >> s2) {
    FORI(26)
      c1[i] = c2[i] = 0;
    FORUI(s1.size())
      ++c1[s1[i]-'A'];
    FORUI(s2.size())
      ++c2[s2[i]-'A'];

    // Poorly written: Substitution cipher can substitute to self, and results may not coincide... which is not at all what the problem tells you :(

    sort(c1, c1+26);
    sort(c2, c2+26);

    bool ok = true;
    FORJ(26) {
      if(c1[j] != c2[j]) {
	ok = false;
	break;
      }
    } // FORJ
    if(ok)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  } // while cin >>
} // int main
