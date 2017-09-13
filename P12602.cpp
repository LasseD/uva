int main() {
  string s;
  FORCAS {
    cin >> s;
    int d = 0;
    for(int i = 0; i < 3; ++i)
      d = 26*d + s[i]-'A';
    int a = 0;
    
    for(int i = 4; i <= 7; ++i) {
      a = 10*a + s[i]-'0';
    }

    if(100 >= ABS(a-d))
      cout << "nice" << endl;
    else
      cout << "not nice" << endl;
  }
  return 0;
}
