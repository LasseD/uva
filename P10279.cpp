int main() {
  string board[11], touch[11];
  FORCAS {
    if(cas > 0)
      cout << endl;
    GI(N);
    bool dead = false;
    FORI(N)
      cin >> board[i];
    FORI(N) {
      cin >> touch[i];
      FORJ(N) {
	if(touch[i][j] == 'x' && board[i][j] == '*')
	  dead = true;
      }
    }
    // Output:
    FORY(N) {
      FORX(N) {
	bool mine = board[y][x] == '*';
	bool hit = touch[y][x] == 'x';
	if(dead && mine)
	  cout << '*';
	else if(!hit)
	  cout << '.';
	else {
	  int cnt = 0;
	  for(int yy = y-1; yy <= y+1; ++yy) {
	    if(yy < 0 || yy >= N)
	      continue;
	    for(int xx = x-1; xx <= x+1; ++xx) {
	      if(xx < 0 || xx >= N)
		continue;
	      if(board[yy][xx] == '*')
		++cnt;
	    }
	  }
	  cout << cnt;
	}
      }
      cout << endl;
    }
  }
  return 0;
}
