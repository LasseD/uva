#define EMPTY -1
#define MINE -2

struct Box {
  int above, below, left, right;
  Box() : above(-1), below(-1), left(-1), right(-1) {}
  bool inside(int x, int y) const {
    return true;
    if(x == left || x == right || y == above || y == below)
      return true; // Fast track.
    return x >= left && (right == -1 || x <= right) && y >= below && (above == -1 || y <= above);
  }
};

void add(int x, int y, int R, int C, int *grid, vector<PI> &v, const Box &b1, const Box &b2) {
  if(x < 0 || y < 0 || x >= C || y >= R) {
    return; // Out of bounds.
  }
  if(grid[y*C+x] == EMPTY && (b1.inside(x,y) || b2.inside(x,y)))
    v.push_back(PI(x,y));
}

int spread(const PI from, const PI to, int * const grid, const int R, const int C, const Box &b1, const Box &b2) {
  int wave = 0;
  vector<PI> v;
  v.push_back(from);
  while(!v.empty()) {
    vector<PI> v2;
    FORIT(vector<PI>, v) {
      PI pos = *it;
      if(pos == to)
	return wave;
      if(grid[pos.YY*C+pos.XX] != EMPTY)
	continue;
      grid[pos.YY*C+pos.XX] = wave;
      //cerr << pos.XX << "," << pos.YY << ": " << wave << endl;
      add(pos.XX-1, pos.YY, R, C, grid, v2, b1, b2);
      add(pos.XX+1, pos.YY, R, C, grid, v2, b1, b2);
      add(pos.XX, pos.YY-1, R, C, grid, v2, b1, b2);
      add(pos.XX, pos.YY+1, R, C, grid, v2, b1, b2);
    }
    ++ wave;
    v = v2;
  }
  return -1;
}

void setBox(PI p, Box &box, int R, int C, bool *freeR, bool *freeC) {
  for(int y = p.YY; y < R; ++y) {
    if(freeR[y]) {
      box.above = y;
      break;
    }
  }
  for(int y = p.YY; y >= 0; --y) {
    if(freeR[y]) {
      box.below = y;
      break;
    }
  }
  for(int x = p.XX; x < C; ++x) {
    if(freeC[x]) {
      box.right = x;
      break;
    }
  }
  for(int x = p.XX; x >= 0; --x) {
    if(freeC[x]) {
      box.left = x;
      break;
    }
  }
}

int main() {
  int R, C, bombRows, bombColumns, row, column;
  while(true) {
    cin >> R >> C;
    if(R == 0 && C == 0)
      return 0;
    int *grid = new int[R*C];
    bool *freeR = new bool[R];
    bool *freeC = new bool[C];
    memset(grid, EMPTY, R*C*sizeof(int));
    memset(freeR, true, R*sizeof(bool));
    memset(freeC, true, C*sizeof(bool));
    cin >> bombRows;
    FORI(bombRows) {
      cin >> row >> bombColumns;
      FORJ(bombColumns) {
	cin >> column;
	freeR[row] = freeC[column] = false;
	grid[row*C+column] = MINE;
      }
    }
    PI from, to;
    cin >> from.YY >> from.XX >> to.YY >> to.XX;
    Box fromBox, toBox;
    setBox(from, fromBox, R, C, freeR, freeC);
    setBox(to, toBox, R, C, freeR, freeC);

    int ret = spread(from, to, grid, R, C, fromBox, toBox);
    if(ret == -1)
      die();
    cout << ret << endl;

    delete[] grid;
    delete[] freeR;
    delete[] freeC;
  }
}
