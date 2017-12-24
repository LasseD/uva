bool blocked[75*3][75*3];
int CC, RR;

int clear(int x, int y) {
  if(x < 0 || y < 0 || x >= CC || y >= RR || blocked[y][x])
    return 0;
  blocked[y][x] = true;
  int ret = 1;
  ret += clear(x-1, y);
  ret += clear(x+1, y);
  ret += clear(x, y-1);
  ret += clear(x, y+1);
  return ret;
}

int main() {
  for(int cas = 1; true; ++cas) {
    GI(C); GI(R); if(C == 0 && R == 0) return 0;
    CC = C*3; RR = R*3;

    FORY(RR) {
      FORX(CC) {
	blocked[y][x] = false;
      }
    }
    for(int y = 1; y < RR; y+=3) {
      for(int x = 1; x < CC; x+=3) {
	blocked[y][x] = true;
      }
    }

    FORY(R) {
      GS(s);
      FORX(C) {
	if(s[x] == '/') {
	  blocked[3*y][3*x+2] = true;
	  blocked[3*y+2][3*x] = true;
	}
	else {
	  blocked[3*y][3*x] = true;
	  blocked[3*y+2][3*x+2] = true;
	}
      } // FORX
    } // FORY
    /*
    cerr << "MAZE" << endl;
    FORY(RR) {
      FORX(CC)
	cerr << (blocked[y][x] ? '*' : ' ');
      cerr << endl;
    }//*/

    // Clear border-touching paths:
    FORX(CC) {
      clear(x, 0);
      clear(x, RR-1);
    }
    FORY(RR) {
      clear(0, y);
      clear(CC-1, y);
    }

    int best = 0;
    int cycles = 0;
    FORY(RR) {
      FORX(CC) {
	int b = clear(x, y)/3;
	if(b > 0)
	  ++cycles;
	best = MAX(best, b);
      }
    }

    cout << "Maze #" << cas << ":" << endl;
    if(cycles == 0)
      cout << "There are no cycles." << endl;
    else
      cout << cycles << " Cycles; the longest has length " << best << "." << endl;
    cout << endl;
  } // while true
} // int main
