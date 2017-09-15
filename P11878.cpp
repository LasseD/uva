int main() {
  int ret = 0;
  
  char w[200], c;
  while(cin.getline(w, 200)) {
    int a = 0, b = 0, d = 0;
    int i = 0;
    while(isdigit(c = w[i])) {
      a = 10*a + c - '0';
      ++i;
    }
    while((c = w[i]) != '+' && c != '-')
      ++i;
    bool isPlus = c == '+';
    while(!isdigit(c = w[i]))
      ++i;
    while(isdigit(c = w[i])) {
      b = 10*b + c - '0';
      ++i;
    }
    // Read result:
    while(!isdigit(c = w[i])) {
      if(c == '?') {
	d = -10000;
	break;
      }
      ++i;
    }

    while(isdigit(c = w[i])) {
      d = 10*d + c - '0';
      ++i;
    }

    
    if(isPlus) {
      if(a+b == d)
	++ret;
    }
    else {
      if(a-b == d)
	++ret;
    }
    //cerr << "a=" << a << ", b=" << b << ", +:" << isPlus << ", c=" << d << endl;
  }
  cout << ret << endl;
  return 0;
}
