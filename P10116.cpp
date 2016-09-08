#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main() {
  int H, W, startX, visited[100], walkX[100], walkY[100];
  string s;
  while(true) {
    cin >> H >> W >> startX; --startX;
    if(H == 0 && W == 0 && startX == -1)
      return 0;
    memset(visited, 0, 100*sizeof(int));

    for(int y = 0; y < H; ++y) {
      cin >> s;
      for(int x = 0; x < W; ++x) {
	switch(s[x]) {
	case 'N':
	  walkX[10*y+x] = 0;
	  walkY[10*y+x] = -1;
	  break;
	case 'S':
	  walkX[10*y+x] = 0;
	  walkY[10*y+x] = 1;
	  break;
	case 'E':
	  walkX[10*y+x] = 1;
	  walkY[10*y+x] = 0;
	  break;
	case 'W':
	  walkX[10*y+x] = -1;
	  walkY[10*y+x] = 0;
	  break;
	}
      }
    }
    int X = startX;
    int Y = 0;
    int time = 1;
    while(X >= 0 && Y >= 0 && X < W && Y < H && visited[10*Y+X] == 0) {
      visited[10*Y+X] = time;
      int x = X;
      X += walkX[10*Y+x];
      Y += walkY[10*Y+x];
      ++time;
    }
    if(X >= 0 && Y >= 0 && X < W && Y < H)
      cout << visited[10*Y+X]-1 << " step(s) before a loop of " << time-visited[10*Y+X] << " step(s)" << endl;
    else
      cout << time-1 << " step(s) to exit" << endl;
  }
}
