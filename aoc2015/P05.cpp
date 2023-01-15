string naughty[4] = {"ab", "cd", "pq", "xy"};

int main() {
  int answer1 = 0, answer2 = 0;
  string s;
  while(cin >> s) {
    cout << "Test " << s << endl;
    bool ok = true;
    FORI(4) {
      if(s.find(naughty[i]) != string::npos) {
	ok = false;
	break;
      }
    }
    if(ok) {
      int wow = 0;
      FORUI(s.size()) {
	char c = s[i];
	if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c =='u') {
	  wow++;
	}
      }
      if(wow >= 3) {
	for(int i = 1; i < (int)s.size(); i++) {
	  if(s[i] == s[i-1]) {
	    answer1++;
	    break;
	  }
	}
      }
    }

    // Answer 2:
    ok = false;
    for(int i = 2; i < (int)s.size(); i++) {
      if(s[i] == s[i-2]) {
	ok = true;
	break;
      }
    }
    if(ok) {
      ok = false;
      for(int i = (int)s.size()-2; i >= 2; i--) {
	char c1 = s[i], c2 = s[i+1];
	for(int j = 0; j+2 <= i; j++) {
	  if(c1 == s[j] && c2 == s[j+1]) {
	    ok = true;
	    break;
	  }
	}
	if(ok) {
	  answer2++;
	  break;
	}
      }
    } // if ok
  }
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
