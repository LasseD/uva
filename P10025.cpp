#include <iostream>
#include <cmath>

using namespace std;

int sumDigitsToN(int n) {
  return n*(n+1)/2;
}

int main() {
  int cases, k;
  cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      cout << endl;
    cin >> k;
    if(k < 0)
      k = -k;
    // find first n so: 1 + 2 + 3 + ... n = n(n+1)/2 = m >= k.
    int n = (int)sqrt(k);
    int m;
    while((m = sumDigitsToN(n)) < k || n == 0)
      ++n;
    
    if(k == m) {
      cout << n << endl; // done :)
    }
    else {
      if((m-k) % 2 == 0) {
	cout << n << endl; // even diff => ok.
      }
      else { // make up an uneven difference
	if(n % 2 == 0)
	  cout << n+1 << endl; // Need the next uneven number.
	else
	  cout << n+2 << endl; // Need the next uneven number.
      }
    }
  }
  return 0;
}
