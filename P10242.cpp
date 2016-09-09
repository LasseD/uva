#include <stdio.h>
#include <iostream>

using namespace std;

typedef pair<double,double> PP;
#define X first
#define Y second

int main() {
  PP a[4];
  while(cin >> a[0].X >> a[0].Y) {
    for(int i = 1; i < 4; ++i)
      cin >> a[i].X >> a[i].Y;
    if(a[0] == a[2]) {
      swap(a[0],a[1]);
    }
    else if(a[0] == a[3]) {
      swap(a[0],a[1]);
      swap(a[2],a[3]);
    }
    else if(a[1] == a[3]) {
      swap(a[2],a[3]);
    }
    // now a[1] == a[2].
    double x = a[0].X+(a[3].X-a[2].X);
    double y = a[0].Y+(a[3].Y-a[2].Y);
    printf("%.3lf %.3lf\n", x, y);
  }
}
