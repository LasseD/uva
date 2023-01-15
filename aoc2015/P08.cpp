int main() {
  LL all = 0, some = 0, p2 = 0;
  string s;
  while(cin >> s) {
    all += s.size();
    int reduced = 2; // End quotes.
    for(int i = 0; i < (int)s.size(); i++) {
      char c = s[i];
      if(c != '\\')
	continue;
      reduced++;
      i++;
      c = s[i];
      if(c == '\\' || c == '"') {
	// OK.
      }
      else {
	i+=2;
	reduced+=2;
      }
    }
    some += s.size() - reduced;
    // Part 2:
    for(int i = 0; i < (int)s.size(); i++) {
      char c = s[i];
      if(c == '\\' || c == '"') {
	p2++;
      }
    }
    p2+=2;
  }
  cout << "Answer 1: " << (all-some) << endl;
  cout << "Answer 2: " << p2 << endl;
}
