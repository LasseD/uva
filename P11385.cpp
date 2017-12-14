int main() {
  // Build fibs:
  map<long,int> FIB;
  FIB[1] = 0;
  FIB[2] = 1;
  long pp = 1;
  long p = 2;
  long f;
  int idx = 2;
  while((f = pp+p) < 4000000000) {
    FIB[f] = idx++;
    pp = p;
    p = f;
  }

  char ret[109];
  FORCAS {
    vector<int> firstLine;
    vector<char> secondLine;
    memset(ret, ' ', sizeof(ret));
    int max = -1;
    
    GI(N);
    FORI(N) {      
      GI(x);      
      int y = FIB[x];
      firstLine.push_back(y);
      if(y > max)
	max = y;
    }
    string s;
    getline(cin, s);
    getline(cin, s);
    //cerr << "Cipher: '" << s << "'" << endl;
    FORUI(s.size()) {
      char c = s[i];
      if(c >= 'A' && c <= 'Z')
	secondLine.push_back(c);
    }

    FORUI(firstLine.size()) {      
      int x = firstLine[i];
      ret[x] = secondLine[i];
    }
    ret[max+1] = '\0';
    cout << ret << endl;
  }
  return 0;
}
