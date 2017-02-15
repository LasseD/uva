typedef pair<PI,int> PIM;

struct Field {
  bool wall, visited[3];
};

bool add(bool commit, int x, int y, int R, int C, Field grid[][300], vector<PIM> &v, int move) {
  if(x < 0 || y < 0 || x >= C || y >= R) {
    return false; // Out of bounds.
  }
  if(grid[y][x].wall) {
    return false;
  }
  if(commit)
    v.push_back(PIM(PI(x,y), move));
  return true;
}

int spread(const PI from, const PI to, Field grid[][300], const int R, const int C) {
  //cerr << "From " << from.XX << "," << from.YY << ", to " << to.XX << "," << to.YY << endl;
  int wave = 0;
  vector<PIM> v;
  v.push_back(PIM(from,2)); // PIM moves 0, 1, 2.
  while(!v.empty()) {
    vector<PIM> v2;
    FORIT(vector<PIM>, v) {
      PI pos = it->first;
      if(grid[pos.YY][pos.XX].wall)
	continue;
      if(pos == to)
	return wave;

      int lastMove = it->second;
      if(grid[pos.YY][pos.XX].visited[lastMove])
	continue;
      grid[pos.YY][pos.XX].visited[lastMove] = true;

      int curMove = (lastMove+1)%3;
      //cerr << pos.XX << "," << pos.YY << ": " << wave << " walk " << lastMove << ", now: " << curMove << endl;
      FORI(curMove+1) {
	if(!add(i == curMove, pos.XX-1-i, pos.YY, R, C, grid, v2, curMove))
	  break;
      }
      FORI(curMove+1) {
	if(!add(i == curMove, pos.XX+1+i, pos.YY, R, C, grid, v2, curMove))
	  break;
      }
      FORI(curMove+1) {
	if(!add(i == curMove, pos.XX, pos.YY-1-i, R, C, grid, v2, curMove))
	  break;
      }
      FORI(curMove+1) {
	if(!add(i == curMove, pos.XX, pos.YY+1+i, R, C, grid, v2, curMove))
	  break;
      }
    }
    ++wave;
    v = v2;
  }
  return -1;
}

int main() {
  int R, C;
  Field grid[300][300];
  string line;
  PI from, to;

  FORCAS {
    cin >> R >> C;
    FORY(R) {
      cin >> line;
      FORX(C) {
	Field &f = grid[y][x];
	f.visited[0] = f.visited[1] = f.visited[2] = false; // Not visited yet.
	f.wall = (line[x] == '#');
	if(line[x] == 'S')
	  from = PI(x,y);
	else if(line[x] == 'E')
	  to = PI(x,y);
      } // x
    } // y
    int ret = spread(from, to, grid, R, C);
    if(ret == -1)
      cout << "NO" << endl;
    else
      cout << ret << endl;
  }
}
