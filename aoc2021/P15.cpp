int Q[100][100], risk[500][500];
typedef pair<int,PI> PI3; // risk lv, pos
int nx[4] = {0,0,1,-1};
int ny[4] = {1,-1,0,0};

int height = 0, width, HEIGHT, WIDTH;
int getQ(int x, int y) {
  int X = x%width, Y = y%height;
  int ret = Q[Y][X];
  int dx = x/width, dy = y/height;
  ret += dx + dy;
  while(ret >= 10)
    ret -= 9;
  return ret;
}

int main() {
  string s;
  while(cin >> s) {
    width = (int)s.size();
    FORX(width)
      Q[height][x] = s[x]-'0';
    height++;
  }
  cout << "Read board size " << width << " x " << height << endl;

  HEIGHT = 5*height;
  WIDTH = 5*width; // For part 1 use 1 instead of 5
  FORY(HEIGHT) {
    FORX(WIDTH) {
      risk[y][x] = -1;
    }
  }
  
  // Always add min risk neighbor:
  set<PI3> ready;
  ready.insert(PI3(0, PI(0,0)));
  
  while(risk[HEIGHT-1][WIDTH-1] == -1) {
    if(ready.empty()) {
      cerr << "ERROR" << endl;
      return 0;
    }
    const PI3 pi3 = *(ready.begin());
    ready.erase(pi3);
    const PI &p = pi3.second;
    if(risk[p.YY][p.XX] != -1) {
      continue; // Already handled
    }
    int r = pi3.first;
    risk[p.YY][p.XX] = r;
    // Prep neighbours:
    FORI(4) {
      int x = p.XX + nx[i];
      int y = p.YY + ny[i];
      if(x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT && risk[y][x] == -1) {
	ready.insert(PI3(r+getQ(x, y), PI(x,y)));
      }
    }
  }
  cout << risk[HEIGHT-1][WIDTH-1] << endl;
}
