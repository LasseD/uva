#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

#define LEN 1026

int main() {
  int *grid = new int[LEN*LEN];
  int *sums = new int[LEN*LEN];
  int cases, d, n, rat, x, y;
  cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    // Reset:
    memset(grid, 0, LEN*LEN*sizeof(int));
    // Read input:
    cin >> d >> n;
    for(int i = 0; i < n; ++i) {
      cin >> x >> y >> rat;
      ++x; // [0,1024] -> [1,1025]
      ++y;
      grid[x*LEN+y] = rat;
    }

    // Compute sums:
    for(x = 0; x < LEN; ++x) {
      sums[x] = sums[x*LEN] = 0; // All positions (0,x), (x,0) have 0 rats.
    }
    int sumAll = 0;
    for(x = 1; x < LEN; ++x) {
      for(y = 1; y < LEN; ++y) {
	rat = grid[x*LEN+y];
	sumAll += rat;
	sums[x*LEN+y] = rat + sums[x*LEN+y-1] + sums[(x-1)*LEN+y] - sums[(x-1)*LEN+y-1];
      }
    }
    //cerr << "SUM ALL: " << sumAll << ", d=" << d << endl;

    int bestRat = 0;
    int bestX = 0;
    int bestY = 0;
    for(x = 1; x+d < LEN; ++x) {
      int xMin = x-d-1;
      if(xMin < 0)
	xMin = 0;
      int xMax = x+d;
      for(y = 1; y+d < LEN; ++y) {
	int yMin = y-d-1;
	if(yMin < 0)
	  yMin = 0;
	int yMax = y+d;
	int curRat = sums[xMax*LEN+yMax] + sums[xMin*LEN+yMin] - sums[xMax*LEN+yMin] - sums[xMin*LEN+yMax];
	if(curRat > bestRat) {
	  //cerr << "Improved attack! x=" << x << ", y=" << y << ", x,yMin=" << xMin << "," << yMin << ", x,yMax=" << xMax << "," << yMax << ": " << curRat << endl;
	  bestX = x-1;
	  bestY = y-1;
	  bestRat = curRat;
	}
      }
    }
    cout << bestX << " " << bestY << " " << bestRat << endl;
  }
}
