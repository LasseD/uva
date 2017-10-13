int main() {
  bool b[1001];
  FORCAS {
    int total, n, bar;
    cin >> total >> n;
    memset(b, false, sizeof(b));
    b[0] = true;
    
    FORI(n) {
      cin >> bar;
      for(int len = total; len >= bar; --len) {
	b[len] |= b[len-bar];
      }
    }
    if(b[total])
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}
