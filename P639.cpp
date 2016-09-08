#include <iostream>
#include <cstdio>

using namespace std;

#define ROOK 0
#define EMPTY 1
#define WALL 2

void run(const int N, int * const board, const int cur, int &max) {
  // try to ad a new rook:
  for(int x = 0; x < N; ++x) {
    for(int y = 0; y < N; ++y) {
      if(board[N*y+x] != EMPTY)
	continue;
      // See if any other rook challenges this position:
      bool ok = true;
      // Up:
      for(int yy = y+1; ok && yy < N; ++yy) {
	if(board[N*yy+x] == ROOK)
	  ok = false;
	if(board[N*yy+x] == WALL)
	  break;
      }
      // down:
      for(int yy = y-1; ok && yy >= 0; --yy) {
	if(board[N*yy+x] == ROOK)
	  ok = false;
	if(board[N*yy+x] == WALL)
	  break;
      }
      // Right:
      for(int xx = x+1; ok && xx < N; ++xx) {
	if(board[N*y+xx] == ROOK)
	  ok = false;
	if(board[N*y+xx] == WALL)
	  break;
      }
      // Left:
      for(int xx = x-1; ok && xx >= 0; --xx) {
	if(board[N*y+xx] == ROOK)
	  ok = false;
	if(board[N*y+xx] == WALL)
	  break;
      }
      if(!ok) 
	continue; 

      if(cur+1 > max)
	max = cur+1;
      board[N*y+x] = ROOK;
      run(N, board, cur+1, max);
      board[N*y+x] = EMPTY;
    } // for x
  } // for y
} // run()

int main() {
  int N, board[16];  
  string s;
  while(true) {
    cin >> N;
    if(N == 0)
      return 0;
    for(int i = 0; i < N; ++i) {
      cin >> s;
      for(int j = 0; j < N; ++j)
	board[N*i+j] = s[j] == '.' ? EMPTY : WALL;
    }

    int max = 0;
    run(N, board, 0, max);
    cout << max << endl;
  }
}
