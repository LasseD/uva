int main() {
  long *ret = new long[1000001];
  ret[3] = 0;
  for(long i = 4; i <= 1000000; ++i)
    ret[i] = ret[i-1] + ((i-2)/2) * ((i-1)/2);
  int N;
  while(true) {
    cin >> N;
    if(N < 3)
      return 0;
    cout << ret[N] << endl;
  }
}
