// Clean up input by removing first two lines and "/dev/grid/node-x", and "T", and replace "-y" with space.
int main() {
  PI data[32][32];
  string ignore;
  int x, y, size, used, sizeX = 0, sizeY = 0;
  while(cin >> x >> y >> size >> used >> ignore >> ignore) {
    data[y][x] = PI(size,used);
    sizeX = max(x+1, sizeX);
    sizeY = max(y+1, sizeY);
  }
  cout << "Read grid: " << sizeX << " x " << sizeY << endl;

  long answer = 0;
  FORX(sizeX) {
    FORY(sizeY) {
      PI &a = data[y][x];
      if(a.second == 0) { // No used of a
	continue;	
      }
      FORI(sizeX) {
	FORJ(sizeY) {
	  if(!(x==i&&y==j)) { // Not the same
	    PI &b = data[j][i];
	    if(a.second <= (b.first-b.second)) {
	      answer++;
	    }
	  }
	} // FORJ
      } // FORI
    } // FORY
  } // FORX
  cout << answer << endl; // 814 too low
}
