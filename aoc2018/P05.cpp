bool kill(char a, char b) {
  if(a > b)
    swap(a,b);
  a += 'a'-'A';
  return a == b;
}

int react(string &input, int size) {
  stack<char> s;
  FORUI(size) {
    char c = input[i];
    if(s.size() > 0 && kill(s.top(),c)) {
      s.pop();
    }
    else {
      s.push(c);
    }
  }
  return (int)s.size();
}

int main() {
  GS(s);
  cout << "Answer 1: " << react(s, (int)s.size()) << endl;
  int best = (int)s.size();
  FORI(26) {
    string s2 = s;
    int size = 0;
    FORUJ(s2.size()) {
      char c = s2[j];
      if(c == (char)('a'+i) || c == (char)('A'+i)) {
	// Skip!
      }
      else {
	s2[size++] = c;
      }
    }
    best = min(best, react(s2, size));
  }
  cout << "Answer 2: " << best << endl;
}
