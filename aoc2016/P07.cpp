bool abba(char *s) {
  FORI(4) {
    char c = s[i];
    if(c == ']' || c == '[' || c == 0) {
      return false;
    }
  }
  if(s[0] == s[1])
    return false;
  return s[0] == s[3] && s[1] == s[2];
}

bool aba(char *s, PC &pc) {
  FORI(3) {
    char c = s[i];
    if(c == ']' || c == '[' || c == 0) {
      return false;
    }
  }
  if(s[0] == s[1])
    return false;
  if(s[0] != s[2])
    return false;
  pc.first = s[0];
  pc.second = s[1];
  return true;
}

int main() {
  int answer1 = 0, answer2 = 0, all = 0;
  string s;
  while(cin >> s) {
    set<PC> ABA, BAB;
    bool isIn = false;
    bool hasOutside = false;
    bool hasInside = false;
    FORUI(s.size()) {
      char c = s[i];
      if(c == ']') {
	isIn = false;
      }
      else if(c == '[') {
	isIn = true;
      }
      else {
	if(abba(&s[i])) {
	  if(isIn)
	    hasInside = true;
	  else
	    hasOutside = true;
	}
	PC pc;
	if(aba(&s[i], pc)) {
	  if(isIn) {
	    BAB.insert(pc);
	  }
	  else {
	    ABA.insert(pc);
	  }
	}
      }
    }
    if(hasOutside && !hasInside) {
      //cout << "1: " << s << endl;
      answer1++;
    }
    FORIT(set<PC>, ABA) {
      PC pc = *it;
      swap(pc.first, pc.second);
      if(BAB.find(pc) != BAB.end()) {
	cout << "2: " << pc.second << pc.first << pc.second << " / " << pc.first << pc.second << pc.first << " " << s << endl;
	answer2++;
	break;
      }
    }
    all++;
  }
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl; // Less than 232
  cout << "Total lines: " << all << endl;
}
