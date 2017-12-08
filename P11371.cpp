int main() {
  string s;
  long cnt[10];
  while(cin >> s) {
    if(s == "0") {
      cout << "0 - 0 = 0 = 9 * 0" << endl;
      continue;
    }

    // Reset:
    FORI(10)
      cnt[i] = 0;

    FORUI(s.size()) {
      ++cnt[s[i]-'0'];
    }
    long max = 0, min = 0;
    FORI(10) {
      long digit = 9-i;
      FORJ(cnt[digit])
	max = 10*max + digit;
    }
    if(cnt[0] > 0) {
      // Min may not start with 0:
      for(long i = 1; i <= 9; ++i) {
	if(cnt[i] > 0) {
	  min = i;
	  --cnt[i];
	  break;
	}
      }
    }
    FORI(10) {
      long digit = i;
      FORJ(cnt[digit])
	min = 10*min + digit;      
    }

    long diff = max-min;
    cout << max << " - " << min << " = " << diff << " = 9 * " << diff/9 << endl;
  }
}
