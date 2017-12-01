#define LEN 100

int go(int x) {
  int ret = 1;
  FORI(x) {
    ret *= x;
    ret %= 10;
  }
  return ret;
}

int main() {
  int ret[LEN];
  ret[0] = 0;
  for(int i = 1; i < LEN; ++i) {
    ret[i] = (ret[i-1] + go(i))%10;
  }
  while(true) {
    GS(s); if(s == "0") return 0;
    int y;
    if(s.size() < 5)
      y = atoi(s.c_str())%100;
    else
      y = 10*(s[s.size()-2]-'0') + s[s.size()-1]-'0';
    cout << ret[y] << endl;
  }  
}
