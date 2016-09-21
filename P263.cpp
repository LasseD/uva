#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

long top(long n) {
  long counters[10];
  for(long i = 0; i < 10; ++i)
    counters[i] = 0;
  while(n > 0) {
    ++counters[n%10];
    n/=10;
  }
  long ret = 0;
  for(long i = 9; i >= 0; --i) {
    while(counters[i]-- > 0)
      ret = 10*ret + i;
  }
  return ret;
}

long flip(long n) {
  long ret = 0;
  while(n > 0) {
    ret = 10*ret + (n%10);
    n/=10;
  }
  return ret;
}

int main() {
  long N;
  while(true) {
    cin >> N;
    if(N == 0)
      return 0;
    cout << "Original number was " << N << endl;
    long len = 1;
    set<int> seen;
    for(; true; ++len) {
      long t = top(N);
      long f = flip(t);
      N = t-f;
      cout << t << " - " << f << " = " << N << endl;
      if(seen.find(N) != seen.end())
	break;
      seen.insert(N);
    }
    cout << "Chain length " << len << endl << endl;
  }
}
