// Replace , with space in input
typedef pair<PI,PI> Line;
int main() {
  vector<Line> lines;
  int a, b, c, d, miX=99999,miY=99999,maX=-99999,maY=-999999;
  string s;
  while(cin >> a >> b >> s >> c >> d) {
    lines.push_back(Line(PI(a,b), PI(c,d)));
    miX = min(miX, min(a,c));
    miY = min(miY, min(b,d));
    maX = max(maX, max(a,c));
    maY = max(maY, max(b,d));
  }
  cout << lines.size() << " lines read. Max: " << maX << ", " << maY << endl;
  int Q[1000][1000];
  FORI(1000){
    FORJ(1000) {
      Q[j][i] = 0;
    }
  }
  FORIT(vector<Line>, lines) {
    int x1 = it->XX.XX, x2 = it->YY.XX, y1 = it->XX.YY, y2 = it->YY.YY;
    if(x1 == x2) {
      for(int y = min(y1,y2); y <= max(y1,y2); y++) {
	Q[y][x1]++;
      }
    }
    else if(y1 == y2) {
      for(int x = min(x1,x2); x <= max(x1,x2); x++) {
	Q[y1][x]++;
      }
    }
    else {
      int dx = x2 > x1 ? 1 : -1;
      int dy = y2 > y1 ? 1 : -1;
      for(int x = x1, y = y1; true; x+=dx, y+=dy) {
	Q[y][x]++; // Only part 2
	if(x == x2)
	  break;
      }
    }
  }
  int answer1 = 0;
  FORI(1000){
    FORJ(1000) {
      if(Q[j][i] > 1)
	answer1++;
    }
  }
  cout << answer1 << endl;
}
