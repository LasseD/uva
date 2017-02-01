void run(string pattern, vector<int> &pos, unsigned int posI) {
  if(posI == pos.size()) {
    cout << pattern << endl;
    return;
  }
  FORI(10) {
    pattern[pos[posI]] = (char)(i+'0');
    run(pattern, pos, posI+1);
  }
}

int main() {
  int n, q;
  while(cin >> n) {
    cout << "--" << endl;
    string s, pattern;
    vector<string> dic;
    FORI(n) {
      cin >> s;
      dic.push_back(s);
    }
    cin >> q;
    FORI(q) {
      cin >> pattern;
      FORIT(vector<string>, dic) {
	stringstream ss;
	int size = 0;
	vector<int> pos;
	FORUJ(pattern.size()) {
	  if(pattern[j] == '0') {
	    ss << '#';
	    pos.push_back(size);
	    ++size;
	  }
	  else {
	    ss << *it;
	    size += it->size();
	  }
	}
	ss >> s;
	run(s, pos, 0);
      }
    }
  }
  return 0;
}
