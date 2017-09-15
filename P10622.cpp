int main() {
  long long N;
  while(true) {
    cin >> N;
    if(N == 0)
      return 0;
    long long absN = N < 0 ? -N : N;
    int bestPow = 1; // Always works.
    for(int p = 2; p <= 32; ++p) {
      if(N < 0)
	++p; // Only uneven powers work for negative numbers.
      long long r = (long)(0.5+pow((double)absN, 1.0/p));
      if(r == 1)
	continue;
      
      long long recreated = r;
      for(int exp = 1; exp < p; ++exp)
	recreated *= r;
      if(recreated == absN)
	bestPow = p;
    }
    ///cerr << N << " => ";
    cout << bestPow << endl;
  }
}
