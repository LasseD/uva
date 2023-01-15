int G[1000][1000];

int main() {
  FORI(1000) {
    FORJ(1000) {
      G[i][j] = 0;
    }
  }
  G[500][500] = 1;
  GI(q);

  PI p(500,500);
  int id = 1;
  int len = 1, walked = 0;
  int dir = 0;
  while(id != q) {
    switch(dir%4) {
    case 0:
      p.XX++;
      break;
    case 1:
      p.YY--;
      break;
    case 2:
      p.XX--;
      break;
    case 3:
      p.YY++;
      break;      
    }
    walked++;
    id++;
    int sum = 0;
    for(int y = p.YY -1; y <= p.YY+1; y++) {
      for(int x = p.XX-1; x <= p.XX+1; x++) {
	sum += G[y][x];
      }
    }
    G[p.YY][p.XX] = sum;
    if(sum > q) {
      cout << "Answer 2: " << sum << endl;
      return 0; // Part 2.
    }
    //cout << id << ": " << p.XX << " " << p.YY << endl;
    if(len == walked) {
      walked = 0;
      dir++;
      if(dir % 2 == 0)
	len++;
    }
  }
  cout << "Answer 1: " << (abs(p.XX-500)+abs(p.YY-500)) << endl;
}
