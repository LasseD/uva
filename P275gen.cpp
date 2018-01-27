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

  int cases = 500;
  for(int j = 0; j < cases; ++j) {
    int n = rand() % 500;
    int q = n + 1 + (rand() % 500);
    cout << n << " " << q << endl;
  }
  cout << "0 0" << endl;
  return 0;
}
