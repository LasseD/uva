#include <iostream>
#include <stdio.h>

using namespace std;

int test(int N, double a0, double an1, double *c, double a1) {
  double ai = a0;
  double ai1 = a1;
  for(int i = 0; i < N; ++i) {
    double ai2 = 2.0*(ai1 + c[i])-ai;
    /*if(ai2 > 1000)
      return -1;
    if(ai2 < 1000)
      return 1;//*/
    ai = ai1;
    ai1 = ai2;
  }
  if(ai1 >= an1)
    return 1;
  return -1;
}

int main() {
  int cases, N;
  double a0, an1, c[3000];
  cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      cout << endl;
    cin >> N >> a0 >> an1;
    for(int i = 0; i < N; ++i)
      cin >> c[i];
    double a1Max = 1000;
    double a1Min = -1000;
    while(a1Max > a1Min + 1e-4) {
      double a1Mid = (a1Max+a1Min)/2.0;
      //      cerr << "Try " << a1Mid << endl;
      int t = test(N, a0, an1, c, a1Mid);
      if(t == 1)
	a1Max = a1Mid;
      else
	a1Min = a1Mid;
    }
    printf("%.2lf\n", a1Min);
  }
  return 0;
}
