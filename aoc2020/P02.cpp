// Remove - and : from input
int main() {
  int answer1 = 0, answer2 = 0, mi, ma;
  char c; string s;
  while(cin >> mi >> ma >> c >> s) {
    int cnt = 0;
    FORUI(s.size()) {
      if(s[i] == c) {
	cnt++;
      }
    }
    if(mi <= cnt && cnt <= ma) {
      answer1++;
    }
    char c1 = s[mi-1], c2 = s[ma-1];
    if(c1 == c && c2 != c || c1 != c && c2 == c) {
      answer2++;
    }
  }
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
