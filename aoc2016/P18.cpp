int main() {
  GS(row);
  string row2 = row;
  long safe = 0;
  FORUI(row.size()) {
    if(row[i] == '.') {
      safe++;
    }
  }
  cout << row << endl;

  bool traps[3];
  GI(ROWS);
  FORJ(ROWS-1) {
    FORI((int)row.size()) {
      traps[0] = (i-1 >= 0) && row[i-1] == '^';
      traps[1] = row[i] == '^';
      traps[2] = (i+1 < row.size()) && row[i+1] == '^';
      
      if(( traps[0] &&  traps[1] && !traps[2]) ||
	 (!traps[0] &&  traps[1] &&  traps[2]) ||
	 ( traps[0] && !traps[1] && !traps[2]) ||
	 (!traps[0] && !traps[1] &&  traps[2])) {
	row2[i] = '^';
      }
      else {
	row2[i] = '.';
	safe++;
      }      
    } // FORI row.size()
    swap(row,row2);
    cout << row << endl;
  } // FORJ 39

  cout << safe << endl;
}
