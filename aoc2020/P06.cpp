int main() {
  int answer1 = 0, answer2 = 0; bool firstPerson = true;
  set<char> S, intersection; string s;
  while(true) {
    bool hasLine = getline(cin, s);
    if(!hasLine || s == "") {
      answer1 += S.size();
      S.clear();
      firstPerson = true;
      cout << "Adding " << intersection.size() << endl;
      answer2 += intersection.size();
      intersection.clear();
    }
    if(!hasLine)
      break;
    if(s == "")
      continue;
    // Part 1:    
    FORUI(s.size()) {
      S.insert(s[i]);
    }
    // Part 2:
    if(firstPerson) { // Take all:
      FORUI(s.size()) {
	intersection.insert(s[i]);
      }
      firstPerson = false;
      cout << "First person => " << intersection.size() << endl;
    }
    else { // Intersect:
      set<char> T;
      FORUI(s.size()) {
	if(intersection.find(s[i]) != intersection.end()) {
	  T.insert(s[i]);
	}
      }
      cout << "Size intersection: " << intersection.size() << " from " << T.size() << endl;
      intersection = T;
    }
  }
  cout << answer1 << endl;
  cout << answer2 << endl;
}
