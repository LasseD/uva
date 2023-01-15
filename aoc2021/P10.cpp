int main() {
  map<char,int> scores;
  scores[')'] = 3;
  scores[']'] = 57;
  scores['}'] = 1197;
  scores['>'] = 25137;
  map<char,char> match;
  match['{'] = '}';
  match['}'] = '{';
  match['('] = ')';
  match[')'] = '(';
  match['<'] = '>';
  match['>'] = '<';
  match['['] = ']';
  match[']'] = '[';
  vector<LL> v;
  map<char,int> p2;
  p2[')'] = 1;
  p2[']'] = 2;
  p2['}'] = 3;
  p2['>'] = 4;
  
  string line;
  LL answer1 = 0;
  while(getline(cin, line)) {
    stack<char> s;
    bool error = false;
    FORI(line.size()) {
      char c = line[i], top;
      switch(c) {
      case '[':
      case '(':
      case '<':
      case '{':
	s.push(c);
	break;
      default:
	top = s.top(); s.pop();
	if(match[top] != c) {
	  cout << line << " - Expected " << match[top] << ", but found " << c << " instead." << endl;
	  answer1 += scores[c];
	  error = true;
	}
	break;
      }
      if(error)
	break;
    }
    if(error)
      continue;
    // Part 2:
    cout << line << " - Complete by adding ";
    LL score = 0;
    while(!s.empty()) {
      score = 5*score + p2[match[s.top()]];
      cout << match[s.top()];
      s.pop();
    }
    cout << ": " << score << endl;
    v.push_back(score);
  }
  sort(v.begin(), v.end());
  cout << answer1 << endl;
  cout << v[v.size()/2] << endl;
}
