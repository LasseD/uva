int main() {
  string NEG = "negative";
  string TWENTY[20] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
		       "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
  string TENS[8] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
  string BIG[3] = {"hundred","thousand", "million"};

  map<string,long> M;
  FORI(20)
    M[TWENTY[i]] = i;
  map<string,long> tens;
  FORI(8)
    M[TENS[i]] = 10*(i+2);  

  while(true) {
    bool neg = false;
  
    string s;
    if(!getline(cin, s))
      return 0;
    stringstream ss; ss << s;
    
    long ret = 0;
    long thousand = 0;
    while(ss >> s) {
      if(s == NEG) {
	neg = true;
	continue;
      }
      if(s == BIG[2]) { // Million:
	ret = thousand * 1000000;
	thousand = 0;
	continue;
      }
      if(s == BIG[1]) { // thousand:
	ret += thousand * 1000;
	thousand = 0;
	continue;
      }
      if(s == BIG[0]) { // hundred:
	thousand *= 100;
	continue;
      }
      thousand += M[s];
    }    

    ret += thousand;
    if(neg)
      ret = -ret;
    cout << ret << endl;
  }
}
