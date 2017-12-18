int main() {
  string line, s;

  while(true) {
    getline(cin, line);
    if(line == "*")
      return 0;

    transform(line.begin(),line.end(),line.begin(),::tolower);
    stringstream ss; ss << line;
    ss >> s;
    char letter = s[0];
    bool ok = true;
    while(ss >> s) {
      if(s[0] != letter) {
	ok = false;
      }
    }
    cout << (ok ? 'Y' : 'N') << endl;
  }
}
