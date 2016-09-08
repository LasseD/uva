#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  int N, K, a[101*101]; // index 101*k+n = how many ways k can add to n.
  while(true) {
    cin >> N >> K;
    if(N == 0 && K == 0)
      return 0;
    // for K = 1 there is no way to add to n using numbers smaller than n:
    for(int n = 0; n <= N; ++n)
      a[101*1+n] = 1;
    for(int k = 2; k <= K; ++k) {
      for(int n = 0; n <= N; ++n) {
	int sum = 0;
	for(int last = 0; last <= n; ++last)
	  sum += a[101*(k-1)+(n-last)];
	a[101*k+n] = sum % 1000000;
      }
    }
    cout << a[101*K+N] << endl;
  }
}
