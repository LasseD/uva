int digits(long x) {
  int ret = 1;
  while(x > 9) {
    x /= 10;
    ++ret;
  }
  return ret;
}

long startingIndexOfNumber(long n) {
  int digitsInN = digits(n);
  long ret = 0;
  long firstOfLength = 1;
  for(int length = 1; length < digitsInN; ++length) {
    long ofThisLength = 9*firstOfLength;
    ret += length*ofThisLength;
    firstOfLength*=10;
  }
  ret += digitsInN*(n-firstOfLength);
  return ret;
}

void printDigit(long digit, long N) {
  int len = digits(N);
  for(int i = 0; i < len-1-digit; ++i) {
    N/=10;
  }
  cout << N%10 << endl;
}

int main() {
  long N;
  while(cin >> N) {
    // Binary search:
    long low = 1;
    long high = N+1;
    while(low+1 < high) {
      long mid = (low+high)/2;
      long idxMid = startingIndexOfNumber(mid);
      if(idxMid >= N)
	high = mid;
      else
	low = mid;
    }
    long idx = startingIndexOfNumber(low);
    //cerr << N << " => " << low << " starting at " << idx << endl;
    printDigit(N-1-idx, low);
  }
  return 0;
}
