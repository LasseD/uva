int main() {
  string s;
  int answer = 0;
  while(getline(cin, s)) {
    stringstream ss; ss << s;
    set<string> S;
    bool ok = true;
    while(ss >> s) {
      sort(&s[0], &s[0]+s.size()); // Only for part 2
      if(S.find(s) != S.end()) {
	ok = false;
	break;
      }
      S.insert(s);
    } // while ss >> s
    if(ok)
      answer++;
  } // while getline
  cout << answer << endl;
}
