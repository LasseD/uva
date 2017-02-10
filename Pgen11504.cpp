#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int,int> Point;
typedef vector<Point> Polygon;
typedef pair<Point,Point> Line;
#define xx first
#define yy second

void makeRandomLine(int max) {
  int a = rand() % max + 1; // between 1 and max, inclusive.
  int b = rand() % max + 1; // between 1 and max, inclusive.

  cout << a << " " << b << endl;
}

int main () {
  /* initialize random seed: */
  srand(time(NULL));

  int cases = 1;
  cout << cases << endl; // test cases
  for(int j = 0; j < cases; ++j) {
    int n = rand() % 10+1; // between 1 and max, inclusive.
    int m = rand() % 10; // between 1 and max, inclusive.
    cout << n << " " << m << endl;
    for(int i = 0; i < m; ++i)
      makeRandomLine(n);
  }
  return 0;
}
