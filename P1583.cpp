#define MX 100001

int sum(int n) {
  int ret = n;
  while(n > 0) {
    ret += n%10;
    n/=10;
  }
  return ret;
}

int main() {
  int generators[MX];
  memset(generators, 0, sizeof(generators));
  for(int i = 1; i < MX; ++i) {
    int s = sum(i);
    if(s < MX && generators[s] == 0)
      generators[s] = i;
  }
  FORCAS {
    GI(x); 
    cout << generators[x] << endl;
  }
  return 0;
}
