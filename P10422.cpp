typedef unsigned long long ULL;

#define EMPTY 0
#define BLACK 1
#define WHITE 2

ULL encode(int *board) {
  ULL ret = 0;
  FORI(25) {
    switch(board[i]) {
    case EMPTY:
      ret = (ret << 2);
      break;
    case WHITE:
      ret = (ret << 2) | WHITE;
      break;
    default:
      ret = (ret << 2) | BLACK;
      break;
    }
  }
  return ret;
}

int decode(ULL encoded, int *board) {
  int ret = 0;
  FORI(25) {
    board[24-i] = encoded & 3;
    if(board[24-i] == EMPTY)
      ret = 24-i;
    encoded >>= 2;
  }
  return ret;
}

void add(int x, int y, int emptyX, int emptyY, int *board, vector<ULL> &v2, map<ULL,int> &m) {
  if(x < 0 || x > 4 || y < 0 || y > 4)
    return;  
  swap(board[5*y+x], board[5*emptyY+emptyX]);
  ULL encoded = encode(board);
  if(m.find(encoded) == m.end()) {
    v2.push_back(encoded);
  }
  swap(board[5*y+x], board[5*emptyY+emptyX]);
}

void buildMap(map<ULL,int> &m) {
  int board[25] = {BLACK,BLACK,BLACK,BLACK,BLACK,
		   WHITE,BLACK,BLACK,BLACK,BLACK,
		   WHITE,WHITE,EMPTY,BLACK,BLACK,
		   WHITE,WHITE,WHITE,WHITE,BLACK,
		   WHITE,WHITE,WHITE,WHITE,WHITE};
  vector<ULL> v;
  v.push_back(encode(board));  
  FORI(11) {
    vector<ULL> v2;
    FORIT(vector<ULL>, v) {
      ULL candidate = *it;
      if(m.find(candidate) != m.end())
	continue;
      m.insert(make_pair(candidate, i));
      int empty = decode(candidate, board);

      /*
      if(i <= 11 && it == v.begin()) {
	cerr << i << ": " << candidate << endl;
	FORY(5) {
	  FORX(5) {
	    cerr << board[y*5+x];
	  }
	  cerr << endl;
	}
      }//*/

      int y = empty / 5;
      int x = empty % 5;
      add(x-2, y-1, x, y, board, v2, m);
      add(x-2, y+1, x, y, board, v2, m);
      add(x-1, y-2, x, y, board, v2, m);
      add(x-1, y+2, x, y, board, v2, m);
      add(x+2, y-1, x, y, board, v2, m);
      add(x+2, y+1, x, y, board, v2, m);
      add(x+1, y-2, x, y, board, v2, m);
      add(x+1, y+2, x, y, board, v2, m);
    }
    v = v2;
  }
}

int main() {
  map<ULL,int> m;
  buildMap(m);
  int board[25];
  char line[20];
  int cases;
  scanf("%d\n", &cases);
  for(int cas = 0; cas < cases; ++cas) {
    FORI(5) {
      gets(line);
      FORJ(5) {
	switch(line[j]) {
	case '0':
	  board[i*5+j] = WHITE;
	  break;
	case '1':
	  board[i*5+j] = BLACK;
	  break;
	default:
	  board[i*5+j] = EMPTY;
	  break;
	}
      }
      //cerr << line << endl;
    }
    ULL encoded = encode(board);

    /*
    cerr << "Trial: " << encoded << endl;
    FORY(5) {
      FORX(5) {
	cerr << board[y*5+x];
      }
      cerr << endl;
    }//*/

    if(m.find(encoded) == m.end())
      cout << "Unsolvable in less than 11 move(s)." << endl;
    else
      cout << "Solvable in " << m[encoded] << " move(s)." << endl;
  }
  return 0;
}
