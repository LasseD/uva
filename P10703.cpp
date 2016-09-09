#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int,int> PP;
typedef vector<PP> Vector;

int main() {
  int W, H, N, x1, y1, x2, y2;
  Vector v[500];
  while(true) {
    cin >> W >> H >> N;
    if(W+H+N == 0)
      return 0;
    for(int y = 0; y < H; ++y)
      v[y].clear();
    for(int i = 0; i < N; ++i) {
      cin >> x1 >> y1 >> x2 >> y2;
      --y1; --y2; --x1; --x2;
      if(x1 > x2)
	swap(x1,x2);
      if(y1 > y2)
	swap(y1,y2);
      for(int y = y1; y <= y2; ++y)
	v[y].push_back(PP(x1,x2));
    }
    int empty = 0;
    for(int y = 0; y < H; ++y) {
      sort(v[y].begin(), v[y].end());
      int lastX = -1;
      for(Vector::const_iterator it = v[y].begin(); it != v[y].end(); ++it) {
	int left = it->first;
	int right = it->second;
	if(left <= lastX+1) {
	  if(lastX < right)
	    lastX = right;
	}
	else {
	  empty += left-lastX-1;
	  lastX = right;
	}
      }
      empty += W-lastX-1;
    }
    if(empty == 0)
      cout << "There is no empty spots." << endl;
    else if(empty == 1)
      cout << "There is one empty spot." << endl;
    else
      cout << "There are " << empty << " empty spots." << endl;
  }
}
