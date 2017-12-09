void decode(string &s) {
  string dec = "OIZEASGTBP";

  FORUI(s.size()) {
    char c = s[i];
    if(isdigit(c))
      s[i] = dec[c-'0'];
  }
}

int main() {
  int cases; scanf("%d\n", &cases);
  for(int cas = 0; cas < cases; ++cas) {
    if(cas > 0)
      cout << endl;
    string line;
    while(true) {
      getline(cin, line);
      if(line.empty())
	break;
      decode(line);
      cout << line << endl;
    }
  }
  return 0;
}
