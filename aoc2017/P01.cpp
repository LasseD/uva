int main() {
  GS(s);
  long answer = 0;
  FORI((int)s.size()) {
    if(s[i] == s[(i+s.size()/2)%s.size()]) { // +1 for part 1
      answer += s[i]-'0';
    }
  }
  cout << answer << endl;
}
