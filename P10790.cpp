int main() { 
  int a, b;
  for(int cas = 1; true; ++cas) {
    cin >> a >> b;
    if(a == 0 && b == 0)
      return 0;
    if(a > b)
      swap(a,b);
    ULL ret = 0;
    ULL clusters = (b*(b-1))/2;
    for(int A = 2; A <= a; ++A) {
      ret += clusters * (A-1);
    }
    cout << "Case " << cas << ": " << ret << endl;
  } // for cas
} // int main
