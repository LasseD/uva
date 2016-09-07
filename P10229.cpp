#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
  long n, m;
  while(cin >> n >> m) {
    long mod = 1 << m;
    //cerr << "n=" << n << ", m=" << m << ", mod=" << mod << endl;
    if(n <= 1 || m == 0) {
      cout << n % mod << endl;
      continue;
    }
    long fPrevPrev = 0, fPrev = 1;
    long i = 1;
    bool cycleCompleted = false;
    long cycleStart = -1;
    long cycleStartPrev;
    long cycleLength = 0;
    while(i < n) {
      ++i;
      long f = (fPrevPrev+fPrev)%mod;
      if(cycleStart == -1 && f < fPrev) {
	cycleStart = f;
	cycleStartPrev = fPrev;
      }
      else if(cycleStart != -1 && !cycleCompleted) {
	++cycleLength;
	if(f == cycleStart && fPrev == cycleStartPrev) {
	  cycleCompleted = true;
	  //cerr << "Cycle length for m=" << m << ": " << cycleLength << endl;
	  long jumpDistance = ((n-i)/cycleLength)*cycleLength;
	  //cerr << "Jump of i=" << i << "->" << (i+jumpDistance) << endl;
	  i += jumpDistance;
	}
      }//*/
      fPrevPrev = fPrev;
      fPrev = f;
    }
    cout << fPrev << endl;
  }
  return 0;
}
