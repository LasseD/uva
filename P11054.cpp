#include <iostream>

using namespace std;

int main() {
  int n, a;
  while(true) {
    cin >> n;
    if(n == 0)
      return 0;
    long long cur = 0;
    unsigned long long ret = 0;
    for(int i = 0; i < n; ++i) {
      cin >> a;
      cur += a;
      if(cur > 0)
	ret += cur;
      else
	ret -= cur;
    }
    cout << ret << endl;
  } // for cas
} // main
