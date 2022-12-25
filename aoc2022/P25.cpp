LL decode1(char c) {
  if(c == '=')
    return -2;
  if(c == '-')
    return -1;
  return c-'0';
}

char encode1(LL x) {
  if(x < -2 || x > 2) {
    cout << "Encoding error: " << x << endl;
    die();
  }
  if(x == -2)
    return '=';
  if(x == -1)
    return '-';
  return (char)('0'+x);
}

string sum2(string a, string b) {
  // Sum:
  stack<char> s;
  int size = (int)max(a.size(),b.size()), carry = 0;
  FORUI(size) {
    char c1 = i >= a.size() ? '0' : a[a.size()-1-i];
    char c2 = i >= b.size() ? '0' : b[b.size()-1-i];
    LL x = decode1(c1) + decode1(c2) + carry;
    // X can be from -5 to 5 (2+2+1)
    carry = x/3;
    x = x-5*carry;
    cout << " ADD " << c1 << " and " << c2 << " carry " << carry << " -> " << x << endl;
    s.push(encode1(x));
  }
  if(carry != 0) {
    cout << " ENCODING CARRY " << carry << endl;
    s.push(encode1(carry));
  }
  
  // Output:
  stringstream ss;
  while(!s.empty()) {
    char c = s.top();
    ss << c;
    s.pop();
  }
  return ss.str();
}

LL decode(string s) {
  LL ret = 0;
  FORI(s.size()) {
    ret = 5*ret + decode1(s[i]);
  }			
  return ret;  
}

int main() {
  string sumS = "";
  LL sumL = 0;
  string s;
  while(cin >> s) {
    sumS = sum2(sumS, s);
    sumL += decode(s);
    cout << s << " is " << decode(s) << " sums: " << sumS << " vs " << sumL << endl;
    if(sumL != decode(sumS)) {
      cerr << "ERROR!: " << sumL << " != " << decode(sumS) << endl;
      return 1;
    }
  }
  cout << "Answer 1: " << sumS << endl;
}
