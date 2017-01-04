#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

/*
Given position n:
Circle size for radius r : 6*r, r > 0, 1 for r = 0.
 */
int main() {
  int n;
  while(cin >> n) {
    if(n == 1) {
      cout << "0 0" << endl;
      continue;
    }
    int r = 1;
    int coreSize = 1;
    while(coreSize + r*6 < n) {      
      coreSize += r*6;
      ++r;
    }
    int circumference = 6*r;
    int side = 6*(n-1-coreSize)/circumference;
    int len = (n-1-coreSize)-side*r;
    //cerr << "n=" << n << ", r=" << r << ", side=" << side << ", len=" << len << endl;
    int x, y;
    switch(side) {
    case 0: // Lower right:
      x = r-1-len;
      y = 1+len;
      break;
    case 1: // Lower left:
      x = -1-len;
      y = r;
      break;
    case 2: // left:
      x = -r;
      y = r-1-len;
      break;
    case 3: // Upper left:
      x = -r+1+len;
      y = -1-len;
      break;
    case 4: // Upper right:
      x = 1+len;
      y = -r;
      break;
    default: // Right:
      x = r;
      y = 1-r+len;
      break;
    }
    cout << x << " " << y << endl;
  }
  return 0;
}
