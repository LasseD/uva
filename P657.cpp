// map[y][x] walk.

void eatX(int x, int y, char map[][50], int W, int H) {
  if('X' != map[y][x])
    return;
  map[y][x] = '*';
  if(x > 0)
    eatX(x-1, y, map, W, H);
  if(x < W-1)
    eatX(x+1, y, map, W, H);
  if(y > 0)
    eatX(x, y-1, map, W, H);
  if(y < H-1)
    eatX(x, y+1, map, W, H);
}

int getDice(int x, int y, char map[][50], int W, int H) {
  if('.' == map[y][x])
    return 0;
  int ret = 0;
  if('X' == map[y][x]) {
    ++ret;
    eatX(x, y, map, W, H);
  }
  map[y][x] = '.';

  if(x > 0)
    ret += getDice(x-1, y, map, W, H);
  if(x < W-1)
    ret += getDice(x+1, y, map, W, H);
  if(y > 0)
    ret += getDice(x, y-1, map, W, H);
  if(y < H-1)
    ret += getDice(x, y+1, map, W, H);

  return ret;
}

int main() {
  int W, H;
  char map[50][50];
  string line;
  for(int cas = 1; true; ++cas) {
    cin >> W >> H;
    if(W == 0 && H == 0)
      return 0;
    FORY(H) {
      cin >> line;
      FORX(W) {
	map[y][x] = line[x];
      }
    }
    
    vector<int> ret;
    FORY(H) {
      FORX(W) {
	int cnt = getDice(x,y, map, W, H);
	if(cnt > 0)
	  ret.push_back(cnt);
      }
    }
    sort(ret.begin(), ret.end());
    cout << "Throw " << cas << endl;
    FORUI(ret.size()) {
      if(i != 0)
	cout << " ";
      cout << ret[i];
    }
    cout << endl << endl;
  } // for cas
}
