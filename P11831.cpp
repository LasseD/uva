#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

int walkTo(string *M, int w, int h, PI &pos, int x, int y) {
  if(x < 0 || y < 0 || x >= w || y >= h)
    return 0;
  if(M[y][x] == '#')
    return 0;
  pos.XX = x;
  pos.YY = y;
  if(M[y][x] == '.')
    return 0;
  M[y][x] = '.';
  return 1;
}

int walk(string *M, int W, int H, PI &pos, int dir) {
  switch(dir) {
  case NORTH:
    return walkTo(M, W, H, pos, pos.XX, pos.YY-1);
  case EAST:
    return walkTo(M, W, H, pos, pos.XX+1, pos.YY);
  case SOUTH:
    return walkTo(M, W, H, pos, pos.XX, pos.YY+1);
  default: //case WEST:
    return walkTo(M, W, H, pos, pos.XX-1, pos.YY);
  }
}

int getBot(char c) {
  if(c == 'N')
    return NORTH;
  if(c == 'S')
    return SOUTH;
  if(c == 'L')
    return EAST;
  if(c == 'O')
    return WEST;
  return -1;
}

int main() {
  int N, M, S, dir;
  PI pos;
  string grid[100], path;
  while(true) {
    cin >> N >> M >> S; // Rows, columns, intructions
    if(N+M+S == 0)
      return 0;
    FORY(N) {
      cin >> grid[y];
      FORX(M) {
	if(-1 != getBot(grid[y][x])) {
	  dir = getBot(grid[y][x]);
	  pos = PI(x,y);
	  grid[y][x] = '.';
	}
      }
    }
    cin >> path;
    int ret = 0;
    FORI(S) {
      switch(path[i]) {
      case 'D':
	dir = (dir+1)%4;
	break;
      case 'E':
	dir = (dir+3)%4;
	break;
      default:
	ret += walk(grid, M, N, pos, dir);
	break;
      }
    }
    cout << ret << endl;
  }
}
