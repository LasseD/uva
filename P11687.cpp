LL len(LL x) {
  int ret = 1;
  while(x > 9) {
    x/=10;
    ++ret;
  }
  return ret;
}

int main() {
  while(true) {
    GS(s);
    if(s == "END")
      return 0;
    
    LL x, prev;
    int i = 1;
    if(s.size() > 5) {
      prev = -1;
      x = s.size();
    }
    else {
      prev = atoi(s.c_str());
      x = len(prev);
    }
    while(prev != x) {
      prev = x;
      x = len(x);
      ++i;
    }
    cout << i << endl;
  }
}
