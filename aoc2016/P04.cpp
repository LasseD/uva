/*
Input cleanup:
Replace [, ] and - with space 
 */
int cnt[26];
int main() {
  int answer = 0;
  string s;
  while(true) {
    stringstream ss;
    // Reset:
    FORI(26) {
      cnt[i] = 0;
    }
    bool any = false;
    while(cin >> s) {
      any = true;
      char c0 = s[0];
      if(c0 >= '0' && c0 <= '9') {
	break;
      }
      FORUI(s.size()) {
	cnt[s[i]-'a']++;
      }
      ss << s << " ";
    }
    //cout << " String scanned: " << s << endl;
    if(!any) {
      cout << answer << endl;
      return 0;
    }
    int id = stoi(s);
    cin >> s; // Checksum
    vector<PIC> v;
    FORI(26) {
      if(cnt[i] > 0)
	v.push_back(PIC(-cnt[i],(char)('a'+i)));
    }
    sort(v.begin(), v.end());
    // Check against checksum:
    bool ok = v.size() >= s.size();
    if(ok) {
      FORUI(s.size()) {
	if(s[i] != v[i].second) {
	  ok = false;
	  break;
	}
      }
    }
    if(ok) {
      answer += id;
      s = ss.str();
      // Output:
      FORUI(s.size()) {
	if(s[i] == ' ')
	  continue;
	int x = (s[i]-'a')+id;
	s[i] = (char)('a'+x%26);
      }
      cout << "OK " << s << " with ID " << id << endl;
    }
  } // while true
} // int main
