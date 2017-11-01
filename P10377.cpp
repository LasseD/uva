char DIR[4] = {'N', 'E', 'S', 'W'};

int main() {
  string maze[66], s, cmd;
  int cases, rows, columns, y, x;
  getline(cin, s);
  stringstream ss1; ss1 << s; ss1 >> cases;
  
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      cout << endl;

    getline(cin, s);
    getline(cin, s);
    stringstream ss2; ss2 << s; ss2 >> rows >> columns;
    //cerr << rows << " rows, " << columns << " columns " << endl;
    
    FORI(rows)
      getline(cin, maze[i]);

    getline(cin, s);
    stringstream ss3; ss3 << s; ss3 >> y >> x;

    --y; --x;
    int dir = 0;

    //cerr << y+1 << " " << x+1 << " " << DIR[dir] << endl;

    bool done = false;
    while(!done) {
      getline(cin, cmd);
      FORUI(cmd.size()) {
	char c = cmd[i];
	//cerr << c << " => ";
	switch(c) {
	case 'R':
	  ++dir;
	  if(dir == 4)
	    dir = 0;
	  break;
	case 'L':
	  --dir;
	  if(dir == -1)
	    dir = 3;
	  break;
	case 'F':
	  switch(dir) {
	  case 0: // north
	    if(maze[y-1][x] != '*')
	      --y;
	    break;
	  case 1: // east
	    if(maze[y][x+1] != '*')
	      ++x;
	    break;
	  case 2: // south
	    if(maze[y+1][x] != '*')
	      ++y;
	    break;
	  default: // west
	    if(maze[y][x-1] != '*')
	      --x;
	    break;
	  }
	  
	  break;
	case 'Q':
	  cout << y+1 << " " << x+1 << " " << DIR[dir] << endl;
	  done = true;
	  break;
	default:
	  break; // space.
	}
	//cerr << y+1 << " " << x+1 << " " << DIR[dir] << endl;
      } // FORUI
    } // while(!done)
  } // FORCAS
  return 0;
}
