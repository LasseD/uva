#include <iostream>
#include <stdio.h>

#define HIT_NONE 0
#define HIT_WHITE 1
#define HIT_BLACK 2

/*
black at top
WHITE at bottom
 */
class Board {
  char board[64];
  int state;

  bool kingAt(bool white, int x, int y) {
    if(x < 0 || y < 0 || x >= 8 || y >= 8)
      return false;
    if(white)
      return board[8*y+x] == 'K';    
    return board[8*y+x] == 'k';
  }
  void tryHitKing(bool white, int x, int y) {
    if(state == HIT_NONE && kingAt(white, x, y)) {
      if(white) {
	state = HIT_WHITE;
	std::cout << "white king is in check." << std::endl;
      }
      else {
	state = HIT_BLACK;
	std::cout << "black king is in check." << std::endl;
      }
    }
  }

  // Bonde
  void pawn(bool white, int x, int y) {
    tryHitKing(!white, x-1, white ? y-1 : y+1);
    tryHitKing(!white, x+1, white ? y-1 : y+1);
  }

  // Taarn
  void rook(bool white, int x, int y) {
    // Up:
    for(int xx = x-1; xx >= 0; --xx) {
      tryHitKing(!white, xx, y);      
      if(board[8*y+xx] != '.')
	break;
    }
    // Down:
    for(int xx = x+1; xx < 8; ++xx) {
      tryHitKing(!white, xx, y);
      if(board[8*y+xx] != '.')
	break;
    }
    // Left:
    for(int yy = y-1; yy >= 0; --yy) {
      tryHitKing(!white, x, yy);
      if(board[8*yy+x] != '.')
	break;
    }
    // Right:
    for(int yy = y+1; yy < 8; ++yy) {
      tryHitKing(!white, x, yy);
      if(board[8*yy+x] != '.')
	break;
    }
  }

  // Loeber
  void bishop(bool white, int x, int y) {
    for(int i = 1; true; ++i) {
      int xx = x-i;
      int yy = y-i;
      if(xx < 0 || yy < 0 || xx >= 8 || yy >= 8)
	break;
      tryHitKing(!white, xx, yy);      
      if(board[8*yy+xx] != '.')
	break;
    }
    for(int i = 1; true; ++i) {
      int xx = x-i;
      int yy = y+i;
      if(xx < 0 || yy < 0 || xx >= 8 || yy >= 8)
	break;
      tryHitKing(!white, xx, yy);      
      if(board[8*yy+xx] != '.')
	break;
    }
    for(int i = 1; true; ++i) {
      int xx = x+i;
      int yy = y-i;
      if(xx < 0 || yy < 0 || xx >= 8 || yy >= 8)
	break;
      tryHitKing(!white, xx, yy);      
      if(board[8*yy+xx] != '.')
	break;
    }
    for(int i = 1; true; ++i) {
      int xx = x+i;
      int yy = y+i;
      if(xx < 0 || yy < 0 || xx >= 8 || yy >= 8)
	break;
      tryHitKing(!white, xx, yy);      
      if(board[8*yy+xx] != '.')
	break;
    }
  }

  // Dronning
  void queen(bool white, int x, int y) {
    bishop(white, x, y);
    rook(white, x, y);
  }

  // Springer
  void knight(bool white, int x, int y) {
    for(int xx = -2; xx <= 2; ++xx) {
      for(int yy = -2; yy <= 2; ++yy) {
	if(xx*xx*yy*yy != 4)
	  continue;
	tryHitKing(!white, x+xx, y+yy);
      }
    }
  }

public:
  bool read() {
    state = HIT_NONE;
    bool anyPieces = false;
    char line[19];
    // Scan for next line with content:
    do {
      gets(line);
    }
    while(line[0] != '.' && !isalpha(line[0]));
    for(int i = 0; i < 8; ++i) {
      if(i != 0)
	gets(line);
      for(int j = 0; j < 8; ++j) {
	board[8*i+j] = line[j];
	if(line[j] != '.')
	  anyPieces = true;
      }
    }
    return anyPieces;
  }

  void check() {
    for(int x = 0; x < 8 && state == HIT_NONE; ++x) {
      for(int y = 0; y < 8 && state == HIT_NONE; ++y) {
	char piece = board[8*y+x];
	switch(piece) {
	case '.':
	  break;
	case 'p':
	case 'P':
	  pawn(piece == 'P', x, y);
	  break;
	case 'r':
	case 'R':
	  rook(piece == 'R', x, y);
	  break;
	case 'b':
	case 'B':
	  bishop(piece == 'B', x, y);
	  break;
	case 'q':
	case 'Q':
	  queen(piece == 'Q', x, y);
	  break;
	case 'n':
	case 'N':
	  knight(piece == 'N', x, y);
	  break;
	}
      }
    }
    if(state == HIT_NONE)
      std::cout << "no king is in check." << std::endl;
  }
};

int main() {
  Board b;
  for(int cas = 1; b.read(); ++cas) {
    std::cout << "Game #" << cas << ": ";
    b.check();
  }
  return 0;
}
