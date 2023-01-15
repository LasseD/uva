int main() {
  int a[26]; string s;
  int with2 = 0, with3 = 0;
  vector<string> v;
  while(cin >> s) {
    v.push_back(s);
    FORI(26) a[i] = 0;
    FORUI(s.size()) {
      a[s[i]-'a']++;
    }
    bool has2 = false, has3 = false;
    FORI(26) {
      if(a[i] == 2)
	has2 = true;
      else if(a[i] == 3)
	has3 = true;
    }
    if(has2)
      with2++;
    if(has3)
      with3++;
  }
  cout << "Answer 1: " << (with2*with3) << endl;

  // Part 2:
  FORI((int)v.size()-1) {
    for(int j = i+1; j < v.size(); j++) {
      string s1 = v[i], s2 = v[j];
      int differences = 0;
      int diffAt;
      FORUK(s1.size()) {
	if(s1[k] != s2[k]) {
	  differences++;
	  diffAt = k;
	}
      }
      if(differences == 1) {
	cout << "Answer 2: " << endl;
	FORUK(s1.size()) {
	  if(k != diffAt)
	    cout << s1[k];
	}
	cout << endl;
	return 0;
      }
    }
  }
}
