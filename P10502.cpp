int main() {
  int height[100][100];
  
  while(true) {
    // Read data:
    GI(rows); if(rows == 0) return 0;
    GI(columns);

    // Reset data:
    ULL ret = 0;
    FORI(columns) {
      FORJ(columns)
	height[i][j] = 0;
    }

    // Run:
    FORI(rows) {
      GS(s);
      FORX(columns) {
	bool full = true;
	for(int width = 0; width + x < columns; ++width) {
	  if(!full || s[x+width] == '0') {
	    height[x][width] = 0;
	    full = false;
	    continue;
	  }
	  ++height[x][width];
	  ret += height[x][width];
	}
      } // FORX
    } // FORI
    cout << ret << endl;
  }
} // int main
