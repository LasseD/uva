/*
Special LIS: Include the element itself!
Algorithm from 
https://en.wikipedia.org/wiki/Longest_increasing_subsequence#Online_algorithms
Section "Efficient algorithms".
No need for the P-array in this assignment.
L is saved in ret.
 */
void lis(int N, int *a, int *ret) {
  int *M = new int[N+1]; // M[i] = First index in a where there is increasing subsequence of length i.
  int L = 0;
  FORI(N) {
    int lo = 1;
    int hi = L;
    //cerr << "L=" << L << ", mid=" << (lo+hi+1)/2 << endl;
    while(lo <= hi) {
      int mid = (lo+hi+1)/2;
      if(a[M[mid]] < a[i])
	lo = mid+1;
      else
	hi = mid-1;
    }
    int newL = lo;

    ret[i] = newL;
    //cerr << " " << ret[i];
    M[newL] = i;
    if(newL > L)
      L = newL;
  }
  //cerr << endl;
  delete[] M;
}

int main() {
  int N, x, A[10000], rA[10000], B[10000], rB[10000];
  while(cin >> N) {
    FORI(N) {
      cin >> x;
      A[i] = rA[N-1-i] = x;
    }
    lis(N, A, B);
    lis(N, rA, rB);
    int ret = 1;
    FORI(N) {
      if(B[i] == 1 || 1 == rB[N-1-i])
	continue;      
      x = B[i];
      if(x > rB[N-1-i])
	x = rB[N-1-i];
      x = 2*x-1;
      if(x > ret)
	ret = x;
    }
    cout << ret << endl;
  }
  return 0;
}
