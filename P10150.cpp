int main() {
  // Read dictionary:
  multimap<string,string> dic;
  string line, s1, s2;
  while(getline(cin, line) && isalpha(line[0])) {
    FORUI(line.size()) {
      string s(line);
      s[i] = '*';
      //cerr << "DIC: '" << s << "' / '" << line << "'" << endl;
      dic.insert(make_pair(s,line));
    }
  }
  // Handle queries:
  bool first = true;
  while(getline(cin, line)) {
    if(!first)
      cout << endl;
    first = false;

    stringstream ss; ss << line;
    ss >> s1 >> s2;
    //cerr << "Query '" << s1 << "' -> '" << s2 << "'" << endl;

    map<string,string> prev;
    vector<string> wave;
    wave.push_back(s1);
    prev.insert(make_pair(s1,s1));
    while(!wave.empty() && prev.find(s2) == prev.end()) {
      vector<string> nextWave;
      FORIT(vector<string>, wave) {
	string s = *it;
	FORUI(s.size()) {
	  string sWildcard(s);
	  sWildcard[i] = '*';
	  //cerr << "Trying '" << sWildcard << "': " << (dic.find(sWildcard) != dic.end()) << endl;
	  if(dic.find(sWildcard) != dic.end()) {	    
	    pair<multimap<string,string>::iterator, multimap<string,string>::iterator> range = dic.equal_range(sWildcard);

	    for(multimap<string,string>::iterator it2 = range.first; it2 != range.second; ++it2) {
	      string val = it2->second;
	      if(prev.find(val) != prev.end())
		continue;

	      //cerr << s << "->" << val << endl;
	      prev.insert(make_pair(val,s));
	      nextWave.push_back(val);
	    } // for it2
	  }
	} // FORUJ
      } // FORIT
      wave = nextWave;
    }
    
    if(prev.find(s2) == prev.end()) {
      cout << "No solution." << endl;
    }
    else {
      stack<string> st;
      while(s1 != s2) {
	st.push(s2);
	s2 = prev[s2];
      }
      cout << s1 << endl;
      while(!st.empty()) {
	cout << st.top() << endl;
	st.pop();
      }
    }
  }
  return 0;
}

