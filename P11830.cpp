int main() {
  while(true) {
    GS(ds); GS(s); if(ds == "0" && s == "0") return 0;
    char digit = ds[0];
    bool firstDigit = true;
    FORUI(s.size()) {
      if(s[i] == digit)
	continue;
      if(s[i] == '0' && firstDigit)
	continue;
      cout << s[i];
      firstDigit = false;
    }
    if(firstDigit)
      cout << 0;
    cout << endl;    
  }
}
