#include <iostream>
#include <stdio.h>

using namespace std;

/*
ceil = floor:
x < k => ceil = 1 => x = ceil * x
k | x = => ceil = k/x => x = ceil * k
k !| x (all other cases) => floor+1 = ceil => x = -x*floor + x*ceil
 */
int main() {
  int N;
  cin >> N;
  long x, k;
  for(int cas = 0; cas < N; ++cas) {
    cin >> x >> k;
    if(x < k) {
      cout << "0 " << x << endl;
    }
    else if(x % k == 0) {
      cout << "0 " << k << endl;
    }
    else {
      cout << -x << " " << x << endl;
    }
  }
  return 0;
}
