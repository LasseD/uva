int main() {
  PI empty;
  char board[5][5];
  string line;
  for(int cas = 1; true; ++cas) {
    getline(cin, line);
    if(line[0] == 'Z')
      return 0;
    FORY(5) {
      FORX(5) {
	board[y][x] = line[x];
	if(line[x] == ' ')
	  empty = PI(x,y);
      }
      getline(cin, line);      
    }
    //cerr << empty.XX << "," << empty.YY << endl;
    bool ok = true;
    while(true) {
      FORUI(line.size() && ok) {
	char move = line[i];
	if(move == '0')
	  break;
	switch(move) {
	case 'A':
	  if(empty.YY == 0)
	    ok = false;
	  else {
	    swap(board[empty.YY][empty.XX], board[empty.YY-1][empty.XX]);
	    --empty.YY;
	  }
	  break;
	case 'L':
	  if(empty.XX == 0)
	    ok = false;
	  else {
	    swap(board[empty.YY][empty.XX], board[empty.YY][empty.XX-1]);
	    --empty.XX;
	  }
	  break;
	case 'B':
	  if(empty.YY == 4)
	    ok = false;
	  else {
	    swap(board[empty.YY][empty.XX], board[empty.YY+1][empty.XX]);
	    ++empty.YY;
	  }
	  break;
	default:
	  if(empty.XX == 4)
	    ok = false;
	  else {
	    swap(board[empty.YY][empty.XX], board[empty.YY][empty.XX+1]);
	    ++empty.XX;
	  }
	  break;
	} // switch
      } // for line && ok
      if(line[line.size()-1] == '0')
	break;
      //cerr << "'" << line[line.size()-1] << "'" << endl;
      getline(cin, line);      
    } // while true

    if(cas != 1)
      cout << endl;
    cout << "Puzzle #" << cas << ":" << endl;
    if(!ok)
      cout << "This puzzle has no final configuration." << endl;
    else {
      FORY(5) {
	cout << board[y][0];
	FORX(4)
	  cout << " " << board[y][x+1];
	cout << endl;
      }
    }
  }
}
