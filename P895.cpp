struct Word {
  int letters[26];
};

int main() {
  Word words[1000];
  int size = 0;
  string line;
  while(true) {
    getline(cin, line);
    if(line[0] == '#')
      break;
    Word &w = words[size++];
    FORI(26)
      w.letters[i] = 0;
    FORUI(line.size()) {
      char c = line[i];
      if(c >= 'a' && c <= 'z')
	++w.letters[c-'a'];
    }
  }
  int letters[26];
  while(true) {
    getline(cin, line);
    if(line[0] == '#')
      return 0;
    FORI(26)
      letters[i] = 0;
    //cerr << "query: " << line << endl;
    FORUI(line.size()) {
      char c = line[i];
      if(c >= 'a' && c <= 'z')
	++letters[c-'a'];
    }
    int ret = 0;
    FORI(size) {
      Word &w = words[i];
      bool ok = true;      
      FORJ(26) {
	if(w.letters[j] > letters[j]) {
	  ok = false;
	  break;
	}
      }
      if(ok)
	++ret;
    }
    cout << ret << endl;
  }
}
