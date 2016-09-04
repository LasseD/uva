#include <iostream>
#include <stdio.h>

using namespace std;

// find x and y so: N = x^3-y^3, minimize y.
// N+y^3 = x^3. Try y=1.. until (y+1)^3-y^3 > N.
int main() {
  int N;
  while(true) {
    cin >> N;
    if(N == 0)
      return 0;
    long x = 1, y = 1, x3 = 1, y3 = 1;
    bool ok = true;
    while(ok && N+y3 != x3) {
      if(N+y3 > x3) {
	++x;
	x3=x*x*x;
      }
      else {
	++y;
	long nextY3 = y*y*y;
	if(nextY3-y3 > N)
	  ok = false;
	y3 = nextY3;
      }
    }
    if(!ok)
      cout << "No solution" << endl;
    else
      cout << x << " " << y << endl;
  }
}
