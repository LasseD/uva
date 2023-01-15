LL meta = 0;

LL read() {
  GI(c); // children
  GI(m); // meta
  vector<LL> v;
  FORI(c) {
    v.push_back(read());
  }
  LL ret = 0;
  FORI(m) {
    GI(x);
    meta += x;
    if(c == 0)
      ret +=x;
    else {
      x--;
      if(x < 0 || x >= v.size()) {
	// skip!
	
      }
      else {
	ret += v[x];
      }
    }
      
  }
  return ret;
}

int main() {
  LL answer2 = read();
  cout << "Answer 1: " << meta << endl;
  cout << "Answer 2: " << answer2 << endl;
}
