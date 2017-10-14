#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <algorithm>

using namespace std;

void makeRandomLine(int n) {
  int x = 0;
  cout << x;
  for(int i = 1; i < n; ++i) {
    if(rand() % 10 < 3) {
      ++x;
    }
    cout << " " << x;    
  }
  cout << endl;
}

int main () {
  /* initialize random seed: */
  srand(time(NULL));

  int cases = 1;
  for(int j = 0; j < cases; ++j) {
    int n = rand() % 10 + 1; // between 1 and max, inclusive.
    int q = 10;//rand() % 10; // between 1 and max, inclusive.
    cout << n << " " << q << endl;
    makeRandomLine(n);
    for(int i = 0; i < q; ++i) {
      int a = rand() % n + 1; // between 1 and max, inclusive.
      int b = rand() % n + 1; // between 1 and max, inclusive.
      if(b < a)
	swap(a, b);
      cout << a << " " << b << endl;
    }
  }
  cout << 0 << endl;
  return 0;
}

