long expMod(long x, long y, long n) {
  if(y == 0)
    return n == 1 ? 0 : 1;
  ULL em = expMod(x, y/2, n);
  if((y & 1) == 1)
    return (x*em*em)%n;
  return (em*em)%n;
}

int main() {
  FORCAS {
    GI(x); GI(y); GI(n);
    cout << expMod(x, y, n) << endl;
  }
  return 0;
}
