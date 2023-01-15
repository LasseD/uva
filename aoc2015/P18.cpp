bool G1[102][102], G2[102][102];

int main() {
  GI(steps);
  FORI(102) {
    FORJ(102) {
      G1[i][j] = G2[i][j] = false;
    }
  }
  string s;
  int W, row = 1;
  while(cin >> s) {
    W = (int)s.size();
    FORI(W) {
      G1[row][i+1] = s[i] == '#';
    }
    row++;
  }
  G1[1][1] = G1[1][W] = G1[W][1] = G1[W][W] = true; // Part 2

  cout << "Initial configuration:" << endl;
  FORY(W) {
    FORX(W) {
      bool b = G1[y+1][x+1];
      cout << (b ? '#' : '.');
    }
    cout << endl;
  }
  cout << endl;
  
  FORI(steps) {
    for(int x = 1; x <= W; x++) {
      for(int y = 1; y <= W; y++) {
	int neighbours = 0;
	for(int xx = x-1; xx <= x+1; xx++) {
	  for(int yy = y-1; yy <= y+1; yy++) {
	    if(!(xx==x&&yy==y) && G1[yy][xx]) {
	      neighbours++;
	    }	      
	  }
	}
	if(G1[y][x]) {
	  G2[y][x] = neighbours == 2 || neighbours == 3;
	}
	else {
	  G2[y][x] = neighbours == 3;
	}
      }
    }
    // Part 2:
    G2[1][1] = G2[1][W] = G2[W][1] = G2[W][W] = true;

    int on = 0;
    cout << "After " << (i+1) << " steps:" << endl;
    FORY(W) {
      FORX(W) {
	bool b = G2[y+1][x+1];
	if(b)
	  on++;
	cout << (b ? '#' : '.');
      }
      cout << endl;
    }
    swap(G1, G2);
    cout << on << " on " << endl;
    cout << endl;
    
  }
}
