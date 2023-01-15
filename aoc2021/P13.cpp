// Replace , and = with space in input. Add -1 -1 between sections
char Q[2000][2000];
int width = 0, height = 0;

int main() {
  FORY(2000) {
    FORX(2000) {
      Q[y][x] = '.';
    }
  }
  int x, y;
  while(cin >> x >> y) {
    if(x == -1)
      break;
    Q[y][x] = '#';
    width = max(width, x+1);
    height = max(height, y+1);
  }
  // Fold:
  string s; char c;
  while(cin >> s >> s >> c >> x) {
    y = x;
    if(c == 'x') {
      if(x < width/2) {
	cerr << "Fold more left!" << endl;
	die();
      }
      for(int xx = x+1; xx < width; xx++) {
	for(int yy = 0; yy < height; yy++) {
	  if(Q[yy][xx] == '#')
	    Q[yy][x - (xx-x)] = '#';
	}
      }
      width = x;      
    }
    else { // y
      if(y < height/2) {
	cerr << "Fold more up!" << endl;
	die();
      }
      for(int yy = y+1; yy < height; yy++) {
	for(int xx = 0; xx < width; xx++) {
	  if(Q[yy][xx] == '#')
	    Q[y - (yy-y)][xx] = '#';
	}
      }
      height = y;
    }
    //break; // For Part 1
  }
  int cnt = 0;
  FORY(height) {
    FORX(width) {
      cout << Q[y][x];
      if(Q[y][x] == '#')
	cnt++;
    }
    cout << endl;
  }
  cout << cnt << endl;
}
